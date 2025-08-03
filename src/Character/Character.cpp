#include "Character.h"

#include <algorithm>
#include <iterator>
#include <memory>

#include "Action/Actions.h"
#include "Game/Game.h"
#include "IAction.h"
#include "ICharacter.h"
#include "Item/NormalAttack.h"
#include "Service/GameService.h"
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

void Character::onAction(std::shared_ptr<IAction> action) {
  for (const auto& item : items_) {
    item->onAction(action);
  }

  switch (action->getType()) {
    case ActionType::BATTLE_START: {
      onGameStart(action);
      break;
    }
    case ActionType::BATTLE_END: {
      onGameEnd(action);
      break;
    }
    case ActionType::ROUND_START: {
      onRoundStart(action);
      break;
    }
    case ActionType::ROUND_END: {
      onRoundEnd(action);
      break;
    }
    case ActionType::TURN_START: {
      onTurnStart(action);
      break;
    }
    case ActionType::TURN_END: {
      onTurnEnd(action);
      break;
    }

    case ActionType::DAMAGE: {
      onDamage(action);
      break;
    }
    default:
      break;
  }
}

void Character::onGameStart(const std::shared_ptr<IAction>& action) {
  return;
}

void Character::onDamage(const std::shared_ptr<IAction>& action) {
  if (action->getType() != ActionType::DAMAGE) {
    return;
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
    return;
  }
  if (!damageAction) {
    abort();
  }
  int raw_damage = damageAction->getDamage();
  auto damage_value = std::max(1, raw_damage - defensePower_);
  health_ -= damage_value;
  auto hurt_action = std::shared_ptr<HurtAction>(
      new HurtAction(damageAction->getFrom(), weak_from_this(), damage_value));
  GameServiceManager::getInstance().GetGameService()->postPendingAction(
      hurt_action);

  if (health_ <= 0) {
    auto death_action =
        std::shared_ptr<DeathAction>(new DeathAction(weak_from_this()));
    GameServiceManager::getInstance().GetGameService()->postPendingAction(
        death_action);
  }
}

nlohmann::json Character::toJson() const {
  nlohmann::json ret = ICharacter::toJson();
  return ret;
}
