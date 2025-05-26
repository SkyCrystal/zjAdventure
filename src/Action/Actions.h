#pragma once

#include "IAction.h"

#include <memory>
#include "Utils.h"

class DamageAction : public IAction {
 public:
  DamageAction(std::weak_ptr<ISelectableTarget> from)
      : IAction(ActionType::DAMAGE, from) {}
  virtual ~DamageAction() = default;
  virtual int getDamage() = 0;
};

class HurtAction : public IAction, public FixedTarget {
 public:
  HurtAction(std::weak_ptr<ISelectableTarget> from,
             std::weak_ptr<ISelectableTarget> me,
             int damage)
      : IAction(ActionType::HURT, from), FixedTarget({me}), damage_(damage) {}
  virtual ~HurtAction() = default;
  virtual int getDamage() { return damage_; }

 private:
  int damage_;
};

class DeathAction : public IAction, public FixedTarget {
 public:
  DeathAction(std::weak_ptr<ISelectableTarget> me)
      : IAction(ActionType::DEATH, me), FixedTarget({me}) {}
  virtual ~DeathAction() = default;
};

class CommonAction : public IAction, public FixedTarget {
 public:
  CommonAction(ActionType type, std::weak_ptr<ISelectableTarget> from)
      : IAction(type, from), FixedTarget({}) {}
  virtual ~CommonAction() = default;
};