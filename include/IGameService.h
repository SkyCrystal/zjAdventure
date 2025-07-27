#pragma once
// 获取游戏状态相关 比如当前关卡等级/回合数
#include <memory>
#include <vector>
#include "IAction.h"

class ICharacter;

class IGameService {
public:
  virtual ~IGameService() = default;
  virtual int getCurrentLevel() const = 0;
  virtual int getCurrentRound() const = 0;
  virtual std::vector<std::shared_ptr<ICharacter>> getCurrentCharacters() const = 0;
  virtual std::shared_ptr<ICharacter> getFirstEnemy(
      const std::shared_ptr<ICharacter>& me) const = 0;
  virtual void postPendingAction(const std::shared_ptr<IAction>& action) = 0;
};
