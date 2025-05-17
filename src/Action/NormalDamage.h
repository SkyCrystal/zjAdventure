#include "Action.h"
#include "Utils.h"

class NormalDamage : public IAction, public TargetFirstEnemy {
 public:
  NormalDamage(std::weak_ptr<ISelectableTarget> from)
      : IAction(ActionType::DAMAGE, from), TargetFirstEnemy(from) {}
  virtual ~NormalDamage() = default;
};
