#pragma once

#include <functional>
#include <memory>
#include <vector>

#include "IAction.h"
#include "IReactable.h"
#include "ISelectableTarget.h"


enum class PriorityLevel {
  HIGHEST = -9999,

  HIGH = -100,
  CHARACTER_STATUS = -99,

  NORMAL = 0,
  CHARACTER_ACTION = 1,

  LOW = 100,

  LOWEST = 9999,
};
class IItem : public ISelectableTarget, public virtual IReactable {
 public:
  IItem(std::string description, PriorityLevel priority)
      : ISelectableTarget(TargetType::ITEM, description), priority_(priority) {}
  virtual ~IItem() = default;
  virtual std::weak_ptr<ISelectableTarget> getOwner() const = 0;
  PriorityLevel priority() const { return priority_; }

 private:
  PriorityLevel priority_ = PriorityLevel::NORMAL;  // 优先级
};
template <>
struct std::less<std::shared_ptr<IItem>> {
  bool operator()(const std::shared_ptr<IItem>& a,
                  const std::shared_ptr<IItem>& b) const {
    return a->priority() < b->priority();
  }
};
