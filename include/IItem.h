#pragma once

#include <memory>
#include <vector>
#include "IAction.h"
#include "IReactiable.h"
#include "ISelectableTarget.h"

class IItem : public ISelectableTarget, public virtual IReactiable {
 public:
  IItem() : ISelectableTarget(TargetType::ITEM) {}
  virtual ~IItem() = default;
  virtual std::weak_ptr<ISelectableTarget> getOwner() const = 0;
};
