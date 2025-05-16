#pragma once

#include <cassert>
#include <memory>

#include "ICharacter.h"

enum class DamageCalcType {
  FIXED,
  PERCENTAGE,
};
template <DamageCalcType dmg_type>
class DamageCalculator {
 public:
  static int calculate(std::weak_ptr<ICharacter> from) {
    switch (dmg_type) {
      case DamageCalcType::FIXED:
        assert(false);
        return 0;
      case DamageCalcType::PERCENTAGE:
        return from.lock()->getAttackPower();
      default:
        assert(false);
    }
  }
  static int calculate(int dmg) {
    switch (dmg_type) {
      case DamageCalcType::FIXED:
        return dmg;
      default:
        assert(false);
        return 0;
    }
  }
};
