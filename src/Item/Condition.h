#pragma once
#include <cstddef>
#include <memory>
#include <vector>

#include "IAction.h"
#include "ICharacter.h"

class Trigger;
class Condition {
 public:
  virtual bool canTrigger(std::shared_ptr<IAction> action, ICharacter* on) = 0;
};
template <bool result>
class AlwaysAt : public Condition {
 public:
  bool canTrigger(std::shared_ptr<IAction> /*action*/,
                  ICharacter* /*on*/) override {
    return result;
  }
};

class Trigger {
 public:
  template <typename T, typename... Args>
    requires std::is_base_of_v<Condition, T>
  static Trigger When(Args&&... args) {
    return Trigger(std::make_unique<T>(std::forward<Args>(args)...));
  }

  Trigger(Trigger&& other) noexcept;
  Trigger& operator=(Trigger&& other) noexcept;

  explicit Trigger() : type_(TriggerType::CONDITION) {
    condition_ = std::make_unique<AlwaysAt<true>>();
  }

  Trigger(std::unique_ptr<Condition> condition);

  template <typename T>
    requires std::is_base_of_v<Condition, T>
  Trigger(T&& condition) {
    Trigger(std::make_unique<T>(std::forward<T>(condition)));
  }
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
  bool canTrigger(std::shared_ptr<IAction> action, ICharacter* on);

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

void test() {
  auto trigger = !(Trigger::When<AlwaysAt<true>>() || AlwaysAt<false>());
  auto t2 = Trigger(AlwaysAt<true>());
  auto t3 = AlwaysAt<true>() || AlwaysAt<false>();
}
