#pragma once

#include "Status.h"

class Stun : public Status {
 public:
  Stun(std::weak_ptr<ICharacter> owner) : Status("Stun", owner) {}
  virtual ~Stun() = default;

 private:
  void onActionImpl(const std::shared_ptr<IAction>& action) override;
};
