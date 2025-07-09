#include "NormalAttack.h"
#include "Action/Damage/NormalDamage.h"
#include "IAction.h"

std::vector<std::shared_ptr<IAction>> NormalAttack::onAction(std::shared_ptr<IAction> action) {
  switch (action->getType()) {
    case ActionType::TURN_START: {
      printf("NormalAttack::onAction\n");
      if (getOwner().lock()->getIndex() == action->getFrom().lock()->getIndex()) {
        printf("NormalAttack::onAction::NormalDamage\n");
        return {std::shared_ptr<NormalDamage>(new NormalDamage(getOwner()))};
      }
    }
    default:
      return {};
  }
}

nlohmann::json NormalAttack::toJson() const {
  nlohmann::json ret = Item::toJson();
  ret["name"] = "NormalAttack";
  return ret;
}
