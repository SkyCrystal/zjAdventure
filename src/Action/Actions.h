#pragma once

#include "IAction.h"
#include "IItem.h"

#include <memory>
#include "Utils.h"

class DamageAction : public IAction {
public:
  DamageAction(std::weak_ptr<ISelectableTarget> from) : IAction(ActionType::DAMAGE, from) {}
  virtual ~DamageAction() = default;
  virtual int getDamage() = 0;
};

class HurtAction : public IAction, public FixedTarget {
public:
  HurtAction(std::weak_ptr<ISelectableTarget> from, std::weak_ptr<ISelectableTarget> me, int damage)
      : IAction(ActionType::HURT, from), FixedTarget({me}), damage_(damage) {}
  virtual ~HurtAction() = default;
  virtual int getDamage() {
    return damage_;
  }

private:
  int damage_;
};

class DeathAction : public IAction, public FixedTarget {
public:
  DeathAction(std::weak_ptr<ISelectableTarget> me)
      : IAction(ActionType::DEATH, me), FixedTarget({me}) {}
  virtual ~DeathAction() = default;
};

class CommonAction : public IAction, public FixedTarget {
public:
  CommonAction(ActionType type, std::weak_ptr<ISelectableTarget> from)
      : IAction(type, from), FixedTarget({}) {}
  virtual ~CommonAction() = default;
  nlohmann::json toJson() const override {
    nlohmann::json j = IAction::toJson();
    j["data"] = data_;
    return j;
  }

public:
  int data_ = 0;
};

class AddItemAction : public IAction, public FixedTarget {
public:
  AddItemAction(std::shared_ptr<ISelectableTarget> from, std::shared_ptr<IItem> item)
      : IAction(ActionType::ADD_ITEM, from), FixedTarget({item}), item_(item) {}
  virtual ~AddItemAction() = default;
  std::shared_ptr<IItem> getItem() const {
    return item_;
  }

private:
  std::shared_ptr<IItem> item_;
};

class RemoveItemAction : public IAction, public FixedTarget {
public:
  RemoveItemAction(std::shared_ptr<ISelectableTarget> from, std::shared_ptr<ISelectableTarget> item)
      : IAction(ActionType::REMOVE_ITEM, from), FixedTarget({item}) {}
  virtual ~RemoveItemAction() = default;

  int getIndex() const {
    return index_;
  }

private:
  int index_;
};
