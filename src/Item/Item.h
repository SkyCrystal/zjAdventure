#pragma once

#include <memory>

#include "Condition.h"
#include "ICharacter.h"
#include "IItem.h"

class Item : public IItem {
 public:
  Item(std::string description,
       std::weak_ptr<ISelectableTarget> owner,
       PriorityLevel priority,
       Trigger&& triggerWhen = Trigger())
      : IItem(description, priority),
        owner_(owner),
        triggerWhen_(std::move(triggerWhen)) {}
  virtual ~Item() = default;
  virtual std::weak_ptr<ISelectableTarget> getOwner() const override {
    return owner_;
  }
  virtual nlohmann::json toJson() const override {
    nlohmann::json ret = ISelectableTarget::toJson();
    return ret;
  }
  virtual void selfErase();

 private:
  std::weak_ptr<ISelectableTarget> owner_;
  Trigger triggerWhen_;
};
