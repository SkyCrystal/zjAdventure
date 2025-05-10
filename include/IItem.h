#pragma once

#include <memory>
#include <vector>
#include "IAction.h"
#include "IReactiable.h"
#include "ISelectableTarget.h"

class IItem : public ISelectableTarget, public IReactiable {
 public:
  IItem() : ISelectableTarget(TargetType::ITEM) {}
  virtual ~IItem() = default;
};
