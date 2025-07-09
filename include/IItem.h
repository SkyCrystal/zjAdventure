#pragma once

#include <memory>
#include <vector>
#include "IAction.h"
#include "IReactable.h"
#include "ISelectableTarget.h"

class IItem : public ISelectableTarget, public virtual IReactable {
public:
  IItem(std::string description) : ISelectableTarget(TargetType::ITEM, description) {}
  virtual ~IItem() = default;
  virtual std::weak_ptr<ISelectableTarget> getOwner() const = 0;
};
