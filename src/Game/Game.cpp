#include "Game.h"

#include <stdlib.h>

#include <iostream>
#include <memory>
#include <vector>

#include "Action/Actions.h"
#include "Action/Damage/NormalDamage.h"
#include "Character/Character.h"
#include "IAction.h"
#include "ISelectableTarget.h"
#include "Item/Attack/NormalAttack.h"
#include "Logger/Logger.h"
#include "Logger/SpdLogger.h"
#include "Service/GameService.h"
#include "Util/Utils.h"

Game::Game()
    : current_state_(GameState::BEFORE_BATTLE),
      turn_count_(0),
      ISelectableTarget(TargetType::SYSTEM, "Game") {
  // 初始化游戏数据
  GameServiceManager::getInstance().AddGameService(this);
  auto spdLogInstance = new SpdLogger();
  spdLogInstance->init("Log.txt");
  GameServiceManager::getInstance().AddLogService(spdLogInstance);
}

Game::~Game() {
  GameServiceManager::getInstance().RemoveGameService();
  // 清理资源
}

// 临时的 先搞两个能打起来的
void Game::InitPlayer() {
  auto player =
      std::shared_ptr<Character>(new Character("Player", 100, 20, 5, false));
  current_characters_.push_back(player);
  current_players_.push_back(player);
  auto item = std::shared_ptr<IItem>(new NormalAttack(player));
  pending_actions_.push(std::shared_ptr<IAction>(
      new AddItemAction(shared_from_this(), std::move(item))));

  auto enemy =
      std::shared_ptr<Character>(new Character("Enemy", 100, 10, 5, true));
  current_characters_.push_back(enemy);
  current_enemies_.push_back(enemy);
  item = std::shared_ptr<IItem>(new NormalAttack(enemy));
  pending_actions_.push(std::shared_ptr<IAction>(
      new AddItemAction(shared_from_this(), std::move(item))));

  onContinuePendingActions();
}

void Game::update() {
  logD() << "update";
  if (current_state_ == GameState::BEFORE_BATTLE) {
    // TODO: 触发开始游戏事件
    InitPlayer();
    auto game_start = std::shared_ptr<CommonAction>(
        new CommonAction(ActionType::BATTLE_START, weak_from_this(), {}));
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
      new CommonAction(ActionType::ROUND_START, weak_from_this(), {}));
  round_start->data_ = ++turn_count_;
  pending_actions_.push(std::move(round_start));
  onContinuePendingActions();

  for (const auto& character : current_characters_) {
    if (!character->isAlive()) {
      continue;
    }
    auto turn_start = std::shared_ptr<CommonAction>(new CommonAction(
        ActionType::TURN_START, weak_from_this(), {character}));
    turn_start->data_ = turn_count_;
    pending_actions_.push(std::move(turn_start));
    onContinuePendingActions();
  }
}

void Game::doAction(const std::shared_ptr<IAction>& action) {
  if (!action->isValid()) {
    return;
  }
  auto from = action->getFrom().lock();
  if (!from) {
    logE() << "action from is null\n";
    return;
  }

  auto owner = getOwner(from);
  if (owner && !owner->isAlive()) {
    logE() << "owner is not alive\n";
    return;
  }
  logD() << "action: " << action->getType();

  switch (action->getType()) {
    case ActionType::ADD_ITEM: {
      auto addItemAction = std::static_pointer_cast<AddItemAction>(action);
      addItem(from, addItemAction->getItem());
      break;
    }
    case ActionType::REMOVE_ITEM: {
      auto removeItemAction =
          std::static_pointer_cast<RemoveItemAction>(action);
      removeItem(from, removeItemAction->getIndex());
      break;
    }
    default:
      break;
  }

  for (const auto& character : current_characters_) {
    character->onAction(action);
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
  if (!action->isValid()) {
    return;
  }
  for (const auto& subAction : action->subActions()) {
    doAction(subAction);
  }
}

void Game::onContinuePendingActions() {
  auto result = std::vector<std::shared_ptr<IAction>>();
  while (!pending_actions_.empty()) {
    auto action = pending_actions_.front();

    pending_actions_.pop();
    doAction(action);
  }
}

void Game::addItem(std::shared_ptr<ISelectableTarget> from,
                   std::shared_ptr<IItem> item) {
  auto targetCharacter = getOwner(item);
  targetCharacter->addItem(item);
}

void Game::removeItem(std::shared_ptr<ISelectableTarget> from, int index) {
  auto targetCharacter = getOwner(from);
  targetCharacter->removeItem(index);
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

void Game::postPendingAction(const std::shared_ptr<IAction>& action) {
  pending_actions_.push(action);
}
