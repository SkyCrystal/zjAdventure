#pragma once
// 角色应当具有的基本能力
#include <memory>
#include <vector>

#include "IAction.h"
#include "IReactiable.h"
#include "ISelectableTarget.h"

class IItem;

class ICharacter : public virtual IReactiable, public ISelectableTarget {
 public:
  ICharacter(std::wstring description)
      : ISelectableTarget(TargetType::CHARACTER, description) {}
  virtual ~ICharacter() = default;
  int getHealth() const { return health_; }
  int getAttackPower() const { return attackPower_; }
  int getDefensePower() const { return defensePower_; }
  virtual bool isEnemy() const = 0;
  bool isAlive() const { return alive_; }
  void setAlive(bool alive) { alive_ = alive; }

 protected:
  int health_;
  int maxHealth_;
  int attackPower_;
  int defensePower_;
  bool isEnemy_;
  bool alive_ = true;

  std::vector<std::shared_ptr<IItem>> items_;
};