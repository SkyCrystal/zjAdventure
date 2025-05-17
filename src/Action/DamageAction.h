#pragma once

#include "IAction.h"

class DamageAction : public virtual IAction {
 public:
  DamageAction(std::shared_ptr<ISelectableTarget> from)
      : IAction(ActionType::DAMAGE, from) {}
  virtual ~DamageAction() = default;
  virtual int getDamage() = 0;
};
