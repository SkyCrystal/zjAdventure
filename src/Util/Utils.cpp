#include "Utils.h"

#include "IGameService.h"
#include "IItem.h"
#include "Service/GameService.h"

std::shared_ptr<ICharacter> getOwner(
    std::shared_ptr<ISelectableTarget> target) {
  switch (target->getTargetType()) {
    case TargetType::CHARACTER:
      return std::dynamic_pointer_cast<ICharacter>(target);
    case TargetType::ITEM:
      return getOwner(
          std::dynamic_pointer_cast<IItem>(target)->getOwner().lock());
    default:
      return std::shared_ptr<ICharacter>();
  }
}

std::vector<std::shared_ptr<ISelectableTarget>> TargetFirstEnemy::getTargets()
    const {
  auto game = GameServiceManager::getInstance().GetGameService();
  if (auto e = game->getFirstEnemy(getOwner(from_.lock()))) {
    return {e};
  }
  return {};
}