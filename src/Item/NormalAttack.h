#include <vector>
#include "IAction.h"
#include "Item.h"

class NormalAttack : public Item {
 public:
  std::vector<std::shared_ptr<IAction>> onAction(
      std::shared_ptr<IAction> action) override;
};
