#include "Utils.h"

#include "Game/GameService.h"
#include "IGameService.h"
#include "IItem.h"

std::shared_ptr<ICharacter> getOwner(
    std::shared_ptr<ISelectableTarget> target) {
  switch (target->getTargetType()) {
    case TargetType::CHARACTER:
      return std::dynamic_pointer_cast<ICharacter>(target);
    case TargetType::ITEM:
      return getOwner(std::dynamic_pointer_cast<IItem>(target)->getOwner());
    default:
      return std::shared_ptr<ICharacter>();
  }
}

std::vector<std::shared_ptr<ISelectableTarget>> TargetFirstEnemy::getTargets()
    const {
  return {GameServiceManager::getInstance().GetGameService()->getFirstEnemy(
      getOwner(from_.lock()))};
}