#include "Character.h"
#include <algorithm>
#include <iterator>
#include <memory>

#include "Action/Actions.h"
#include "IAction.h"
#include "ICharacter.h"
#include "Item/NormalAttack.h"
#include "Utils.h"
Character::Character(std::string description,
                     int health,
                     int attackPower,
                     int defensePower,
                     bool isEnemy)
    : ICharacter(description) {
  health_ = health;
  maxHealth_ = health;
  attackPower_ = attackPower;
  defensePower_ = defensePower;
  isEnemy_ = isEnemy;
}

Character::~Character() {}

std::vector<std::shared_ptr<IAction>> Character::onAction(
    std::shared_ptr<IAction> action) {
  std::vector<std::shared_ptr<IAction>> ret;

  for (const auto& item : items_) {
    auto actions = item->onAction(action);
    ret.insert(ret.end(), std::make_move_iterator(actions.begin()),
               std::make_move_iterator(actions.end()));
  }

  switch (action->getType()) {
    case ActionType::BATTLE_START: {
      auto actions = onGameStart(action);
      ret.insert(ret.end(), std::make_move_iterator(actions.begin()),
                 std::make_move_iterator(actions.end()));
      break;
    }
    case ActionType::BATTLE_END: {
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
  if (!damageAction) {
    abort();
  }
  int raw_damage = damageAction->getDamage();
  auto damage_value = std::max(1, raw_damage - defensePower_);
  health_ -= damage_value;
  auto hurt_action = std::shared_ptr<HurtAction>(
      new HurtAction(damageAction->getFrom(), weak_from_this(), damage_value));
  ret.push_back(hurt_action);

  if (health_ <= 0) {
    auto death_action =
        std::shared_ptr<DeathAction>(new DeathAction(weak_from_this()));
    ret.push_back(death_action);
  }
  return ret;
}

nlohmann::json Character::toJson() const {
  nlohmann::json ret = ICharacter::toJson();
  return ret;
}