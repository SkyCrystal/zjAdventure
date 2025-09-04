#include "Condition.h"

#include <algorithm>

#include "Logger/Logger.h"
#include "Utils.h"

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

bool Trigger::canTrigger(const std::shared_ptr<IAction>& action,
                         ICharacter* on) const {
  switch (type_) {
    case TriggerType::AND: {
      return std::ranges::all_of(subTriggers_,
                                 [action, on](const auto& subTrigger) {
                                   return subTrigger.canTrigger(action, on);
                                 });
    }
    case TriggerType::OR: {
      return std::ranges::any_of(subTriggers_,
                                 [action, on](const auto& subTrigger) {
                                   return subTrigger.canTrigger(action, on);
                                 });
    }
    case TriggerType::NOT: {
      return !subTriggers_[0].canTrigger(action, on);
    }
    case TriggerType::CONDITION: {
      return condition_->canTrigger(action, on);
    }
    default: {
      return false;
    }
  }
}

bool FixedPossibility::canTrigger(const std::shared_ptr<IAction>& action,
                                  ICharacter* on) {
  return RandomGenerator::generateDouble() < possibility_;
}

bool CalculatedPossibility::canTrigger(const std::shared_ptr<IAction>& action,
                                       ICharacter* on) {
  return RandomGenerator::generateDouble() < possibility_(action, on);
}
