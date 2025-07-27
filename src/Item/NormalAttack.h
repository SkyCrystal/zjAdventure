#include <vector>
#include "IAction.h"
#include "Item.h"

class NormalAttack : public Item {
public:
  NormalAttack(std::weak_ptr<ISelectableTarget> owner) : Item("NormalAttack", owner) {
    printf("NormalAttack::NormalAttack of %d\n", owner.lock()->getIndex());
  }
  void onAction(std::shared_ptr<IAction> action) override;
  nlohmann::json toJson() const override;
};
