#include <memory>

#include "IAction.h"
#include "Logger/Logger.h"
#include "Status.h"

bool DecreaseByRound::canContinue(std::shared_ptr<IAction> action,
                                  Status& status) {
  switch (action->getType()) {
    case ActionType::ROUND_END: {
      status.remaining_rounds_--;
      // 负数回合认为永续
      return status.remaining_rounds_ != 0;
    }
    case ActionType::BATTLE_END: {
      // 战斗结束后直接消失
      return false;
    }
    default:
      return true;
  }
}

void Status::onAction(std::shared_ptr<IAction> action) {
  onActionImpl(action);
  if (!count_down_->canContinue(action, *this)) {
    logI() << "Status " << getDescription() << " is expired";
    selfErase();
  }
}
