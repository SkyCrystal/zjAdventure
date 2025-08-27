#pragma once

#include "IItem.h"


class Item : public IItem {
 public:
  Item(std::string description,
       std::weak_ptr<ISelectableTarget> owner,
       PriorityLevel priority)
      : IItem(description, priority), owner_(owner) {}
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
};
