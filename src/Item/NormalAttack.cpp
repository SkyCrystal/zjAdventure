#include "NormalAttack.h"
#include "Action/Damage/NormalDamage.h"
#include "IAction.h"

std::vector<std::shared_ptr<IAction>> NormalAttack::onAction(
    std::shared_ptr<IAction> action) {
  switch (action->GetType()) {
    case ActionType::ROUND_START:
      return {std::make_shared<NormalDamage>(getOwner())};
    default:
      return {};
  }
}
