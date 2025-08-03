#pragma once

#include <functional>
#include <list>
#include <memory>
#include <queue>

#include "ICharacter.h"
#include "IItem.h"
#include "ISelectableTarget.h"

// 最普通的角色模板
class Character : public ICharacter {
 public:
  Character(std::string description,
            int health,
            int attackPower,
            int defensePower,
            bool isEnemy);
  ~Character() override;

  bool isEnemy() const override { return isEnemy_; }
  void onAction(std::shared_ptr<IAction> action) override;

  nlohmann::json toJson() const override;

 private:
  virtual void onGameStart(const std::shared_ptr<IAction>& action);
  virtual void onGameEnd(const std::shared_ptr<IAction>& action) {}
  virtual void onRoundStart(const std::shared_ptr<IAction>& action) {}
  virtual void onRoundEnd(const std::shared_ptr<IAction>& action) {}
  virtual void onTurnStart(const std::shared_ptr<IAction>& action) {}
  virtual void onTurnEnd(const std::shared_ptr<IAction>& action) {}
  // 受到攻击
  virtual void onDamage(const std::shared_ptr<IAction>& action);
  // 受到治疗
  virtual void onHeal(const std::shared_ptr<IAction>& action) {}
  // 受到伤害
  virtual void onHurt(const std::shared_ptr<IAction>& action) {}
};
