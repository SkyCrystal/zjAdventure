#pragma once
// 存储行为信息
// 行为一般需要被外部执行
// 是不是也可以让行为自己去调用游戏服务来触发一些全局事件
#include "ITargetSelector.h"
enum class ActionType {
  UNKNOWN,
  APPEARANCE,
  DAMAGE,
  HEAL,

  TEMP_BUFF,
  PERMANENT_BUFF,

  REMOVE_ITEM,
  ADD_ITEM,
  CREATE,
  DEATH,

  GAME_START,
  GAME_END,
  ROUND_START,
  ROUND_END,
  TURN_START,
  TURN_END,

  MOVE,

};

class IAction : public ITargetSelector {
 public:
  IAction(ActionType actionType) : actionType_(actionType) {}
  virtual ~IAction() = default;
  virtual void OnAction();
  virtual ActionType GetType() const = 0;

 private:
  ActionType actionType_;
};