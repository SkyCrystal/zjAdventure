#pragma once

#include "Status.h"

class Stun : public Status {
 public:
  Stun(std::weak_ptr<ISelectableTarget> owner) : Status("Stun", owner) {}
  virtual ~Stun() = default;

 private:
  void onActionImpl(std::shared_ptr<IAction> action) override;
};
