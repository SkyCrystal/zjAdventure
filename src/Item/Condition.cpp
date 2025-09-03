#include "Condition.h"

Trigger operator!(Trigger&& a) {
  return Trigger(Trigger::TriggerType::NOT, std::move(a));
}

Trigger operator&&(Trigger&& a, Trigger&& b) {
  if (a.type_ != Trigger::TriggerType::AND) {
    a = Trigger(Trigger::TriggerType::AND, std::move(a));
  }
  a.subTriggers_.push_back(std::move(b));
  return a;
}

Trigger operator||(Trigger&& a, Trigger&& b) {
  if (a.type_ != Trigger::TriggerType::OR) {
    a = Trigger(Trigger::TriggerType::OR, std::move(a));
  }
  a.subTriggers_.push_back(std::move(b));
  return a;
}

Trigger::Trigger(Trigger&& other) noexcept
    : type_(other.type_),
      condition_(std::move(other.condition_)),
      subTriggers_(std::move(other.subTriggers_)) {}

Trigger& Trigger::operator=(Trigger&& other) noexcept {
  type_ = other.type_;
  condition_ = std::move(other.condition_);
  subTriggers_ = std::move(other.subTriggers_);
  return *this;
}

Trigger::Trigger(std::unique_ptr<Condition> condition)
    : type_(TriggerType::CONDITION), condition_(std::move(condition)) {}

Trigger::Trigger(TriggerType type, Trigger&& condition) noexcept : type_(type) {
  subTriggers_.push_back(std::move(condition));
}
