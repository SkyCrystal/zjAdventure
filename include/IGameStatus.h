#pragma once
// 获取游戏状态相关 比如当前关卡等级/回合数
#include <memory>
#include <vector>

class ICharacter;

class IGameStatus {
 public:
  virtual ~IGameStatus() = default;
  virtual int getCurrentLevel() const = 0;
  virtual int getCurrentRound() const = 0;
  virtual std::vector<std::weak_ptr<ICharacter>> getCurrentCharacters()
      const = 0;
};