#pragma once

#include <cassert>
#include <memory>

#include "ICharacter.h"

enum class DamageCalcType {
  FIXED,
  ATK_PERCENTAGE,
};
template <DamageCalcType dmg_type>
class DamageCalculator {
 public:
  static int calculate(std::shared_ptr<ICharacter> from, int sum) {
    switch (dmg_type) {
      case DamageCalcType::FIXED:
        return sum;
      case DamageCalcType::ATK_PERCENTAGE:
        return from->getAttackPower() * sum / 100;
      default:
        assert(false);
        return 0;
    }
  }
};
