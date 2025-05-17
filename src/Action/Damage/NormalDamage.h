#include "../DamageAction.h"

#include <memory>
#include "DamageCalculator.h"
#include "Utils.h"


class NormalDamage : public DamageAction, public TargetFirstEnemy {
 public:
  NormalDamage(std::shared_ptr<ISelectableTarget> creator)
      : DamageAction(creator), TargetFirstEnemy(creator) {}
  virtual ~NormalDamage() = default;
  int getDamage() override {
    return DamageCalculator<DamageCalcType::ATK_PERCENTAGE>::calculate(
        getOwner(getFrom()), 100);
  }
};
