#include "Item.h"

#include "Action/Actions.h"
#include "Logger/Logger.h"
#include "Service/GameService.h"

void Item::selfErase() {
  GameServiceManager::getInstance().GetGameService()->postPendingAction(
      std::make_shared<RemoveItemAction>(shared_from_this(),
                                         shared_from_this()));
}

void Item::onAction(std::shared_ptr<IAction> action) {
  auto owner = owner_.lock();
  if (!owner) {
    logC() << "Item owner is empty";
    return;
  }

  if (triggerWhen_.canTrigger(action, owner.get())) {
    onActionTriggered(action);
  }
}
