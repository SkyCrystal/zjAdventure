#pragma once

#include "Item.h"

class IStatusCountDown;

class Status : public Item {
  friend class DecreaseByRound;

 public:
  Status(const std::string& description, std::weak_ptr<ISelectableTarget> owner)
      : Item(description, owner, PriorityLevel::CHARACTER_STATUS) {}
  virtual ~Status() = default;
  // 处理剩余回合数相关的逻辑
  void onAction(std::shared_ptr<IAction> action) final;
  // 处理具体的状态
  virtual void onActionImpl(std::shared_ptr<IAction> action) = 0;
  nlohmann::json toJson() const override;

 protected:
  int level_ = 0;  // 层数
  int remaining_rounds_ =
      0;  // 剩余计数 一般是回合数，但具体使用方式取决于IStatusCountDown
  // 用于判断状态持续时间的类
  IStatusCountDown* count_down_ = nullptr;
};

class IStatusCountDown {
 public:
  virtual bool canContinue(std::shared_ptr<IAction> action, Status& status) = 0;
  virtual ~IStatusCountDown() = default;
};

class DecreaseByRound : public IStatusCountDown {
 public:
  bool canContinue(std::shared_ptr<IAction> action, Status& status) override;
  ~DecreaseByRound() override = default;
};
