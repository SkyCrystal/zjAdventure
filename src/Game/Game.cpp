#include "Game.h"
#include "Character/Character.h"
#include "Service/GameService.h"

#include "Action/Damage/NormalDamage.h"

#include <memory>
#include "IAction.h"
#include "Util/Utils.h"

Game::Game()
    : currentState(GameState::BEFORE_BATTLE), turnCount(0), isPlayerTurn(true) {
  // 初始化游戏数据
  GameServiceManager::getInstance().AddGameService(this);

  auto player = std::make_shared<Character>(100, 10, 5, false);
  auto enemy = std::make_shared<Character>(100, 10, 5, true);
  current_characters_.push_back(player);
  current_characters_.push_back(enemy);
  current_enemy_ = enemy;
  current_player_ = player;
}

Game::~Game() {
  // 清理资源
}

void Game::update() {
  printf("update\n");
  if (currentState == GameState::BEFORE_BATTLE) {
    // TODO: 触发开始游戏事件

    auto game_start = std::make_shared<CommonAction>(
        ActionType::GAME_START, std::weak_ptr<ISelectableTarget>());
    pending_actions_.push(std::move(game_start));
    onContinuePendingActions();
    currentState = GameState::IN_BATTLE;
    return;
  }

  if (currentState == GameState::BUILD) {
    return;
  }
  // 游戏逻辑更新

  auto round_start = std::make_shared<CommonAction>(
      ActionType::ROUND_START, std::weak_ptr<ISelectableTarget>());
  pending_actions_.push(std::move(round_start));
  onContinuePendingActions();

  for (const auto& character : current_characters_) {
    auto turn_start =
        std::make_shared<CommonAction>(ActionType::TURN_START, character);
    pending_actions_.push(std::move(turn_start));
    onContinuePendingActions();
  }
}

void Game::onContinuePendingActions() {
  auto result = std::vector<std::shared_ptr<IAction>>();
  while (!pending_actions_.empty()) {
    auto action = pending_actions_.front();

    pending_actions_.pop();
    actions_log_.push_back(action);
    printf("action: %d\n", action->getType());
    for (const auto& character : current_characters_) {
      auto actions = character->onAction(action);
      for (auto& action : actions) {
        pending_actions_.push(std::move(action));
      }
    }
  }
}

nlohmann::json Game::getGameStateJson() const {
  nlohmann::json j;
  j["state"] = static_cast<int>(currentState);
  j["turnCount"] = turnCount;
  j["isPlayerTurn"] = isPlayerTurn;

  // 添加玩家数据
  j["player"] = {{"health", current_player_.lock()->getHealth()},
                 {"attackPower", current_player_.lock()->getAttackPower()},
                 {"defensePower", current_player_.lock()->getDefensePower()}};
  j["enemy"] = {{"health", current_enemy_.lock()->getHealth()},
                {"attackPower", current_enemy_.lock()->getAttackPower()},
                {"defensePower", current_enemy_.lock()->getDefensePower()}};
  return j;
}

int Game::getCurrentLevel() const {
  return 0;
}

int Game::getCurrentRound() const {
  return 0;
}

std::vector<std::shared_ptr<ICharacter>> Game::getCurrentCharacters() const {
  std::vector<std::shared_ptr<ICharacter>> result;
  for (auto& character : current_characters_) {
    result.push_back(character);
  }
  return result;
}

std::shared_ptr<ICharacter> Game::getFirstEnemy(
    const std::shared_ptr<ICharacter>& me) const {
  if (current_enemy_.lock()->getIndex() != me->getIndex()) {
    return current_enemy_.lock();
  }
  return current_player_.lock();
}
