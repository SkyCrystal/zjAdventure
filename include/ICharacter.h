#pragma once
// 角色应当具有的基本能力
#include <memory>
#include <vector>

#include "IReactiable.h"
#include "ISelectableTarget.h"

class IItem;

class ICharacter : public IReactiable, public ISelectableTarget {
 public:
  ICharacter() : ISelectableTarget(TargetType::CHARACTER) {}
  virtual ~ICharacter() = default;
  int getHealth() const { return health_; }
  int getAttackPower() const { return attackPower_; }
  int getDefensePower() const { return defensePower_; }
  virtual bool isEnemy() const = 0;

 protected:
  int health_;
  int attackPower_;
  int defensePower_;
  bool isEnemy_;

  std::vector<std::shared_ptr<IItem>> items_;
};