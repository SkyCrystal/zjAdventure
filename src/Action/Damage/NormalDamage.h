#include "../Actions.h"

#include <memory>
#include "DamageCalculator.h"
#include "Utils.h"

class NormalDamage : public DamageAction, public TargetFirstEnemy {
 public:
  NormalDamage(std::weak_ptr<ISelectableTarget> creator)
      : DamageAction(creator), TargetFirstEnemy(creator) {
    printf("NormalDamage::NormalDamage\n");
    damage_ = DamageCalculator<DamageCalcType::ATK_PERCENTAGE>::calculate(
        getOwner(getFrom().lock()), 100);
  }
  virtual ~NormalDamage() = default;
  int getDamage() override { return damage_; }

 private:
  int damage_;
};
