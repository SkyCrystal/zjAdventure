#include "../Actions.h"

#include <memory>
#include "DamageCalculator.h"
#include "Utils.h"

class NormalDamage : public DamageAction, public TargetFirstEnemy {
 public:
  NormalDamage(std::weak_ptr<ISelectableTarget> creator)
      : DamageAction(creator), TargetFirstEnemy(creator) {
    printf("NormalDamage::NormalDamage\n");
    getDamage();
  }
  virtual ~NormalDamage() = default;
  int getDamage() override {
    return DamageCalculator<DamageCalcType::ATK_PERCENTAGE>::calculate(
        getOwner(getFrom().lock()), 100);
  }
};
