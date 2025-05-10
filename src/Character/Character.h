#pragma once

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
  std::vector<std::unique_ptr<IAction>> onAction(
      std::unique_ptr<IAction> action) override;

  int getIndex() const override;

 private:
};
