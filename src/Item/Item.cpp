#include "Item.h"

#include "Action/Actions.h"
#include "Service/GameService.h"


void Item::selfErase() {
  GameServiceManager::getInstance().GetGameService()->postPendingAction(
      std::make_shared<RemoveItemAction>(shared_from_this(),
                                         shared_from_this()));
}
