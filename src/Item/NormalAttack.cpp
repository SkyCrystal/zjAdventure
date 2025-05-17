#include "NormalAttack.h"

std::vector<std::shared_ptr<IAction>> NormalAttack::onAction(
    std::shared_ptr<IAction> action) {
  return {action};
}
