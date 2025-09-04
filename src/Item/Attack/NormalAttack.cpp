#include "NormalAttack.h"

#include <memory>

#include "Action/Damage/NormalDamage.h"
#include "IAction.h"
#include "Logger/Logger.h"
#include "Service/GameService.h"

void NormalAttack::onActionTriggered(const std::shared_ptr<IAction>& action) {
  logD() << "NormalAttack::onAction::NormalDamage\n";
  action->addSubAction(std::make_shared<NormalDamage>(getOwner()));
}

nlohmann::json NormalAttack::toJson() const {
  nlohmann::json ret = Item::toJson();
  ret["name"] = "NormalAttack";
  return ret;
}
