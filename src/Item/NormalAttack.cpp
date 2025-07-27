#include "Action/Damage/NormalDamage.h"
#include "IAction.h"
#include "Logger/Logger.h"
#include "NormalAttack.h"
#include "Service/GameService.h"


void NormalAttack::onAction(std::shared_ptr<IAction> action) {
  switch (action->getType()) {
    case ActionType::TURN_START: {
      logD() << "NormalAttack::onAction\n";
      if (getOwner().lock()->getIndex() == action->getFrom().lock()->getIndex()) {
        logD() << "NormalAttack::onAction::NormalDamage\n";
        GameServiceManager::getInstance().GetGameService()->postPendingAction(
            std::shared_ptr<NormalDamage>(new NormalDamage(getOwner())));
      }
    }
    default:
      return;
  }
}

nlohmann::json NormalAttack::toJson() const {
  nlohmann::json ret = Item::toJson();
  ret["name"] = "NormalAttack";
  return ret;
}
