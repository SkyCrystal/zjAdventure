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
  std::vector<std::shared_ptr<IAction>> onAction(
      std::shared_ptr<IAction> action) override;

  nlohmann::json toJson() const override;

 private:
  virtual std::vector<std::shared_ptr<IAction>> onGameStart(
      std::shared_ptr<IAction> action);
  virtual std::vector<std::shared_ptr<IAction>> onGameEnd(
      std::shared_ptr<IAction> action) {
    return {};
  };
  virtual std::vector<std::shared_ptr<IAction>> onRoundStart(
      std::shared_ptr<IAction> action) {
    return {};
  };
  virtual std::vector<std::shared_ptr<IAction>> onRoundEnd(
      std::shared_ptr<IAction> action) {
    return {};
  };
  virtual std::vector<std::shared_ptr<IAction>> onTurnStart(
      std::shared_ptr<IAction> action) {
    return {};
  };
  virtual std::vector<std::shared_ptr<IAction>> onTurnEnd(
      std::shared_ptr<IAction> action) {
    return {};
  };
  // 受到攻击
  virtual std::vector<std::shared_ptr<IAction>> onDamage(
      std::shared_ptr<IAction> action);
  // 受到治疗
  virtual std::vector<std::shared_ptr<IAction>> onHeal(
      std::shared_ptr<IAction> action) {
    return {};
  };
  // 受到伤害
  virtual std::vector<std::shared_ptr<IAction>> onHurt(
      std::shared_ptr<IAction> action) {
    return {};
  };

  std::vector<std::shared_ptr<IItem>> items_;
};
