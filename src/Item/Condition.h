#pragma once

#include <memory>
#include <type_traits>
#include <vector>

#include "IAction.h"
#include "ICharacter.h"

class Trigger;
class Condition {
 public:
  virtual bool canTrigger(const std::shared_ptr<IAction>& action,
                          ICharacter* on) = 0;
};

template <bool result>
class Always : public Condition {
 public:
  bool canTrigger(const std::shared_ptr<IAction>& action,
                  ICharacter* on) override {
    return result;
  }
};

class WhenRoundStart : public Condition {
  bool canTrigger(const std::shared_ptr<IAction>& action,
                  ICharacter* on) override {
    return action->getType() == ActionType::ROUND_START;
  }
};

class WhenRoundEnd : public Condition {
  bool canTrigger(const std::shared_ptr<IAction>& action,
                  ICharacter* on) override {
    return action->getType() == ActionType::ROUND_END;
  }
};

class WhenMyTurnStart : public Condition {
  bool canTrigger(const std::shared_ptr<IAction>& action,
                  ICharacter* on) override {
    return action->getType() == ActionType::TURN_START &&
           action->getTargets().size() == 1 &&
           action->getTargets()[0]->getIndex() == on->getIndex();
  };
};

class WhenMyTurnEnd : public Condition {
  bool canTrigger(const std::shared_ptr<IAction>& action,
                  ICharacter* on) override {
    return action->getType() == ActionType::TURN_END &&
           action->getTargets().size() == 1 &&
           action->getTargets()[0]->getIndex() == on->getIndex();
  };
};

class WhenEnemyTurnStart : public Condition {
  bool canTrigger(const std::shared_ptr<IAction>& action,
                  ICharacter* on) override {
    return action->getType() == ActionType::TURN_START &&
           action->getTargets().size() == 1 &&
           std::reinterpret_pointer_cast<ICharacter>(action->getTargets()[0])
                   ->isEnemy() != on->isEnemy();
  };
};

class WhenEnemyTurnEnd : public Condition {
  bool canTrigger(const std::shared_ptr<IAction>& action,
                  ICharacter* on) override {
    return action->getType() == ActionType::TURN_END &&
           action->getTargets().size() == 1 &&
           std::reinterpret_pointer_cast<ICharacter>(action->getTargets()[0])
                   ->isEnemy() != on->isEnemy();
  };
};

class FixedPossibility : public Condition {
 public:
  FixedPossibility(double possibility) : possibility_(possibility) {}
  bool canTrigger(const std::shared_ptr<IAction>& action,
                  ICharacter* on) override;

 private:
  double possibility_;
};

class CalculatedPossibility : public Condition {
 public:
  CalculatedPossibility(
      std::function<double(std::shared_ptr<IAction>, ICharacter*)> possibility)
      : possibility_(std::move(possibility)) {}
  CalculatedPossibility(std::function<double()> possibility) {
    possibility_ = [possibility](const std::shared_ptr<IAction>& action,
                                 ICharacter* on) { return possibility(); };
  }
  bool canTrigger(const std::shared_ptr<IAction>& action,
                  ICharacter* on) override;

 private:
  std::function<double(std::shared_ptr<IAction>, ICharacter*)> possibility_;
};

class Trigger {
 public:
  Trigger(Trigger&& other) noexcept;
  Trigger& operator=(Trigger&& other) noexcept;

  explicit Trigger() : type_(TriggerType::CONDITION) {
    condition_ = std::make_unique<Always<true>>();
  }

  Trigger(std::unique_ptr<Condition> condition);

  template <typename T>
    requires std::is_base_of_v<Condition, T>
  Trigger(T&& condition)
      : Trigger(std::make_unique<T>(std::forward<T>(condition))) {}
  enum class TriggerType {
    UNKNOWN,
    AND,
    OR,
    NOT,
    CONDITION,
  };

 private:
  Trigger(TriggerType type, Trigger&& condition) noexcept;

 public:
  virtual ~Trigger() = default;

 public:
  bool canTrigger(const std::shared_ptr<IAction>& action, ICharacter* on) const;

 private:
  TriggerType type_ = TriggerType::UNKNOWN;
  std::unique_ptr<Condition> condition_;
  std::vector<Trigger> subTriggers_;
  friend Trigger operator!(Trigger&& a);

  friend Trigger operator&&(Trigger&& a, Trigger&& b);
  friend Trigger operator||(Trigger&& a, Trigger&& b);
};

Trigger operator!(Trigger&& a);

Trigger operator&&(Trigger&& a, Trigger&& b);
Trigger operator||(Trigger&& a, Trigger&& b);
