#include "IAction.h"
#include "Logger/Logger.h"
#include "Stun.h"

void Stun::onActionImpl(std::shared_ptr<IAction> action) {
  switch (action->getType()) {
    case ActionType::TURN_START: {
      auto target = action->getTargets();
      if (target.empty()) {
        logE() << "Stun target is empty";
        return;
      }
      auto owner = getOwner().lock();
      if (!owner) {
        logE() << "Stun owner is empty";
        return;
      }
      if (target[0] == owner) {
        logI() << "Stun target " << owner->getDescription();
        action->invalidate();
        return;
      }
    }
    default:
      return;
  }
}
