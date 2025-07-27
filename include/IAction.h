#pragma once
// 存储行为信息
// 行为一般需要被外部执行
// 是不是也可以让行为自己去调用游戏服务来触发一些全局事件

#include <nlohmann/json.hpp>
#include "ISelectableTarget.h"
#include "ITargetSelector.h"

class ISelectableTarget;
enum class ActionType {
  UNKNOWN,
  // UI效果
  APPEARANCE,
  // 伤害
  DAMAGE,
  // 治疗
  HEAL,
  // 受到伤害
  HURT,
  // 受到治疗
  HEALED,
  // 临时buff
  TEMP_BUFF,
  // 永久buff
  PERMANENT_BUFF,
  // 移除buff
  REMOVE_BUFF,
  // 移除道具
  REMOVE_ITEM,
  // 添加道具
  ADD_ITEM,
  // 战吼
  CREATE,
  // 死亡
  DEATH,
  // 战斗开始
  BATTLE_START,
  // 战斗结束
  BATTLE_END,
  // 回合开始
  ROUND_START,
  // 回合结束
  ROUND_END,
  // 行动开始
  TURN_START,
  // 行动结束
  TURN_END,

  MOVE,

};

class IAction : public virtual ITargetSelector {
public:
  IAction(ActionType actionType, std::weak_ptr<ISelectableTarget> from)
      : actionType_(actionType), from_(from) {}
  virtual ~IAction() = default;
  virtual ActionType getType() {
    return actionType_;
  }
  std::weak_ptr<ISelectableTarget> getFrom() {
    return from_;
  }
  virtual nlohmann::json toJson() const {
    nlohmann::json ret;
    ret["type"] = static_cast<int>(actionType_);
    ret["from"] = from_.lock()->toJson();
    return ret;
  }
  std::vector<std::shared_ptr<IAction>>& subActions() {
    return subActions_;
  }

  void addSubAction(std::shared_ptr<IAction> action) {
    subActions_.push_back(std::move(action));
  }

private:
  ActionType actionType_;
  std::weak_ptr<ISelectableTarget> from_;
  // 后继事件 用于预期紧接当前事件结算的场景
  std::vector<std::shared_ptr<IAction>> subActions_;
};
