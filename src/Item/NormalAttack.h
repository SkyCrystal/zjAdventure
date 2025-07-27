#include <vector>
#include "IAction.h"
#include "Item.h"
#include "Logger/Logger.h"

class NormalAttack : public Item {
public:
  NormalAttack(std::weak_ptr<ISelectableTarget> owner)
      : Item("NormalAttack", owner, PriorityLevel::CHARACTER_ACTION) {
    logD() << "NormalAttack::NormalAttack of " << owner.lock()->getIndex();
  }
  void onAction(std::shared_ptr<IAction> action) override;
  nlohmann::json toJson() const override;
};
