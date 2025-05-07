// 获取游戏状态相关 比如当前关卡等级/回合数
#include <vector>

class ICharacters;

class IGameStatus {
 public:
  virtual ~IGameStatus() = default;
  virtual int getCurrentLevel() const = 0;
  virtual int getCurrentRound() const = 0;
  virtual std::vector<ICharacters*> getCurrentCharacters() const = 0;
};