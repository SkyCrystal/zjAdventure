#pragma once

#include <memory>

#include "Condition.h"
#include "ICharacter.h"
#include "IItem.h"

class Item : public IItem {
 public:
  Item(const std::string& description,
       std::weak_ptr<ICharacter> owner,
       PriorityLevel priority,
       Trigger&& triggerWhen = WhenMyTurnStart())
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
  virtual void selfErase() override;
  void onAction(std::shared_ptr<IAction> action) final;
  virtual void onActionTriggered(const std::shared_ptr<IAction>& action) = 0;

 private:
  std::weak_ptr<ICharacter> owner_;
  Trigger triggerWhen_;
};
