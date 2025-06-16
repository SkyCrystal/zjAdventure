#include "Game.h"
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <vector>
#include "Action/Damage/NormalDamage.h"
#include "Character/Character.h"
#include "IAction.h"
#include "ISelectableTarget.h"
#include "Service/GameService.h"
#include "Util/Utils.h"

Game::Game()
    : current_state_(GameState::BEFORE_BATTLE),
      turn_count_(0),
      ISelectableTarget(TargetType::SYSTEM, L"Game") {
  // 初始化游戏数据
  GameServiceManager::getInstance().AddGameService(this);

  auto player =
      std::shared_ptr<Character>(new Character(L"Player", 100, 20, 5, false));
  auto enemy =
      std::shared_ptr<Character>(new Character(L"Enemy", 100, 10, 5, true));
  current_characters_.push_back(player);
  current_characters_.push_back(enemy);
  current_enemies_.push_back(enemy);
  current_players_.push_back(player);
}

Game::~Game() {
  // 清理资源
}

void Game::update() {
  printf("update\n");
  if (current_state_ == GameState::BEFORE_BATTLE) {
    // TODO: 触发开始游戏事件

    auto game_start = std::shared_ptr<CommonAction>(
        new CommonAction(ActionType::GAME_START, weak_from_this()));
    pending_actions_.push(std::move(game_start));

    onContinuePendingActions();
    current_state_ = GameState::IN_BATTLE;
    return;
  }

  if (current_state_ == GameState::BUILD) {
    return;
  }
  // 游戏逻辑更新

  auto round_start = std::shared_ptr<CommonAction>(
      new CommonAction(ActionType::ROUND_START, weak_from_this()));
  round_start->data_ = ++turn_count_;
  pending_actions_.push(std::move(round_start));
  onContinuePendingActions();

  for (const auto& character : current_characters_) {
    if (!character->isAlive()) {
      continue;
    }
    auto turn_start = std::shared_ptr<CommonAction>(
        new CommonAction(ActionType::TURN_START, character));
    turn_start->data_ = turn_count_;
    pending_actions_.push(std::move(turn_start));
    onContinuePendingActions();
  }
}

void Game::onContinuePendingActions() {
  auto result = std::vector<std::shared_ptr<IAction>>();
  while (!pending_actions_.empty()) {
    auto action = pending_actions_.front();

    pending_actions_.pop();
    auto from = action->getFrom().lock();
    if (!from) {
      printf("action from is null\n");
      continue;
    }

    auto owner = getOwner(from);
    if (owner && !owner->isAlive()) {
      printf("owner is not alive\n");
      continue;
    }
    printf("action: %d\n", action->getType());
    for (const auto& character : current_characters_) {
      auto actions = character->onAction(action);
      for (auto& action : actions) {
        pending_actions_.push(std::move(action));
      }
    }

    switch (action->getType()) {
      case ActionType::DEATH: {
        owner->setAlive(false);
        // if (character->getIndex() == current_player_.lock()->getIndex()) {
        //   current_state_ = GameState::END;
        //   current_characters_.clear();
        // }
        // if (character->getIndex() == current_enemy_.lock()->getIndex()) {
        //   std::erase_if(current_characters_, [&character](const auto& c) {
        //     return c->getIndex() == character->getIndex();
        //   });
        //   current_state_ = GameState::BUILD;
        //   // trigger item select
        // }
        break;
      }
      default:
        break;
    }
    actions_log_.push_back(action->toJson());
  }
}

nlohmann::json Game::getGameStateJson() const {
  nlohmann::json j;
  j["state"] = static_cast<int>(current_state_);
  j["turn_count_"] = turn_count_;

  j["players"] = nlohmann::json::array();
  for (const auto& player : current_players_) {
    if (auto p = player.lock()) {
      j["players"].push_back(p->toJson());
    }
  }

  j["enemies"] = nlohmann::json::array();
  for (const auto& enemy : current_enemies_) {
    if (auto e = enemy.lock()) {
      j["enemies"].push_back(e->toJson());
    }
  }

  j["battle_round_"] = battle_round_;
  j["actions_log_"] = nlohmann::json::array();
  for (const auto& action : actions_log_) {
    j["actions_log_"].push_back(action);
  }
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
  if (me->isEnemy()) {
    for (const auto& player : current_players_) {
      if (auto p = player.lock()) {
        if (p->isAlive()) {
          return p;
        }
      }
    }
  } else {
    for (const auto& enemy : current_enemies_) {
      if (auto e = enemy.lock()) {
        if (e->isAlive()) {
          return e;
        }
      }
    }
  }
  return nullptr;
}
