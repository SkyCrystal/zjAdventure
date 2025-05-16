#pragma once

#include <list>
#include <memory>

#include "ICharacter.h"
#include "IItem.h"
#include "ISelectableTarget.h"

// 最普通的角色模板
class Character : public ICharacter {
 public:
  Character(int health, int attackPower, int defensePower, bool isEnemy);
  ~Character() override;

  bool isEnemy() const override { return isEnemy_; }
  std::vector<std::shared_ptr<IAction>> onAction(
      std::shared_ptr<IAction> action) override;

  int getIndex() const override;

 private:
  std::list<std::shared_ptr<IAction>> pending_actions_;
};
