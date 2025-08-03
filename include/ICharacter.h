#pragma once
// 角色应当具有的基本能力
#include <memory>
#include <set>
#include <vector>

#include "IAction.h"
#include "IItem.h"
#include "IReactable.h"
#include "ISelectableTarget.h"

class IItem;

class ICharacter : public virtual IReactable, public ISelectableTarget {
 public:
  ICharacter(std::string description)
      : ISelectableTarget(TargetType::CHARACTER, description) {}
  virtual ~ICharacter() = default;
  int getHealth() const { return health_; }
  int getAttackPower() const { return attackPower_; }
  int getDefensePower() const { return defensePower_; }
  virtual bool isEnemy() const = 0;
  bool isAlive() const { return alive_; }
  void setAlive(bool alive) { alive_ = alive; }
  void addItem(std::shared_ptr<IItem> item) { items_.insert(item); }
  void removeItem(int index) {
    std::erase_if(items_,
                  [&index](const auto& i) { return i->getIndex() == index; });
  }
  nlohmann::json toJson() const override {
    nlohmann::json ret = ISelectableTarget::toJson();
    ret["health"] = health_;
    ret["maxHealth"] = maxHealth_;
    ret["attackPower"] = attackPower_;
    ret["defensePower"] = defensePower_;
    ret["isEnemy"] = isEnemy_;
    ret["items"] = nlohmann::json::array();
    for (const auto& item : items_) {
      ret["items"].push_back(item->toJson());
    }
    return ret;
  }

 protected:
  int health_;
  int maxHealth_;
  int attackPower_;
  int defensePower_;
  bool isEnemy_;
  bool alive_ = true;

  std::multiset<std::shared_ptr<IItem>> items_;
};
