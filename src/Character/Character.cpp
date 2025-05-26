#include "Character.h"
#include <algorithm>
#include <iterator>
#include <memory>

#include "Action/Actions.h"
#include "IAction.h"
#include "Item/NormalAttack.h"
#include "Utils.h"
Character::Character(int health,
                     int attackPower,
                     int defensePower,
                     bool isEnemy) {
  health_ = health;
  attackPower_ = attackPower;
  defensePower_ = defensePower;
  isEnemy_ = isEnemy;
}

Character::~Character() {}

std::vector<std::shared_ptr<IAction>> Character::onAction(
    std::shared_ptr<IAction> action) {
  pending_actions_.push(action);
  std::vector<std::shared_ptr<IAction>> ret;
  while (!pending_actions_.empty()) {
    auto actions = onContinuePendingActions();
    ret.insert(ret.end(), std::make_move_iterator(actions.begin()),
               std::make_move_iterator(actions.end()));
  }
  return ret;
}

std::vector<std::shared_ptr<IAction>> Character::onContinuePendingActions() {
  if (pending_actions_.empty()) {
    return {};
  }

  auto action = pending_actions_.front();
  pending_actions_.pop();
  std::vector<std::shared_ptr<IAction>> ret;

  for (const auto& item : items_) {
    auto actions = item->onAction(action);
    ret.insert(ret.end(), std::make_move_iterator(actions.begin()),
               std::make_move_iterator(actions.end()));
  }

  switch (action->getType()) {
    case ActionType::GAME_START: {
      auto actions = onGameStart(action);
      ret.insert(ret.end(), std::make_move_iterator(actions.begin()),
                 std::make_move_iterator(actions.end()));
      break;
    }
    case ActionType::GAME_END: {
      auto actions = onGameEnd(action);
      ret.insert(ret.end(), std::make_move_iterator(actions.begin()),
                 std::make_move_iterator(actions.end()));
      break;
    }
    case ActionType::ROUND_START: {
      auto actions = onRoundStart(action);
      ret.insert(ret.end(), std::make_move_iterator(actions.begin()),
                 std::make_move_iterator(actions.end()));
      break;
    }
    case ActionType::ROUND_END: {
      auto actions = onRoundEnd(action);
      ret.insert(ret.end(), std::make_move_iterator(actions.begin()),
                 std::make_move_iterator(actions.end()));
      break;
    }
    case ActionType::TURN_START: {
      auto actions = onTurnStart(action);
      ret.insert(ret.end(), std::make_move_iterator(actions.begin()),
                 std::make_move_iterator(actions.end()));
      break;
    }
    case ActionType::TURN_END: {
      auto actions = onTurnEnd(action);
      ret.insert(ret.end(), std::make_move_iterator(actions.begin()),
                 std::make_move_iterator(actions.end()));
      break;
    }

    case ActionType::DAMAGE: {
      auto actions = onDamage(action);
      ret.insert(ret.end(), std::make_move_iterator(actions.begin()),
                 std::make_move_iterator(actions.end()));
      break;
    }
    default:
      break;
  }

  return ret;
}

std::vector<std::shared_ptr<IAction>> Character::onGameStart(
    std::shared_ptr<IAction> action) {
  items_.push_back(std::make_shared<NormalAttack>(weak_from_this()));
  return {};
}

std::vector<std::shared_ptr<IAction>> Character::onDamage(
    std::shared_ptr<IAction> action) {
  std::vector<std::shared_ptr<IAction>> ret;
  if (action->getType() != ActionType::DAMAGE) {
    return {};
  }
  auto damageAction = std::dynamic_pointer_cast<DamageAction>(action);
  const auto& target = damageAction->getTargets();
  bool on_self = false;
  for (const auto& t : target) {
    if (t->getIndex() == getIndex()) {
      // attack is on self
      on_self = true;
    }
  }
  if (!on_self) {
    return {};
  }

  auto damage_value = std::max(1, damageAction->getDamage() - defensePower_);
  health_ -= damage_value;
  auto hurt_action = std::make_shared<HurtAction>(
      damageAction->getFrom(), weak_from_this(), damage_value);
  ret.push_back(hurt_action);

  if (health_ <= 0) {
    auto death_action = std::make_shared<DeathAction>(weak_from_this());
    ret.push_back(death_action);
  }
  return ret;
}
