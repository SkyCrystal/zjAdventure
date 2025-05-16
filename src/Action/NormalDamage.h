#include "Action.h"

class NormalDamage : public Action {
 public:
  NormalDamage(std::weak_ptr<ISelectableTarget> from)
      : Action(ActionType::DAMAGE, from) {}
  virtual ~NormalDamage() = default;
};
