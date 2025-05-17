#include "Utils.h"

#include "Game/GameService.h"
#include "IGameService.h"
#include "IItem.h"

std::weak_ptr<ICharacter> getOwner(std::weak_ptr<ISelectableTarget> target) {
  switch (target.lock()->getTargetType()) {
    case TargetType::CHARACTER:
      return std::dynamic_pointer_cast<ICharacter>(target.lock());
    case TargetType::ITEM:
      return getOwner(
          std::dynamic_pointer_cast<IItem>(target.lock())->getOwner());
    default:
      return std::weak_ptr<ICharacter>();
  }
}

std::vector<std::weak_ptr<ISelectableTarget>> TargetFirstEnemy::getTargets()
    const {
  return {GameServiceManager::getInstance().GetGameService()->getFirstEnemy(
      getOwner(from_))};
}