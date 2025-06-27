#pragma once
#include <concepts>

#include "ICharacter.h"
#include "ITargetSelector.h"

// template <typename T>
// concept RefedPtr = requires(T a) {
//   { a.owner_before(a) } -> std::convertible_to<bool>;
// };

std::shared_ptr<ICharacter> getOwner(std::shared_ptr<ISelectableTarget> target);

class TargetFirstEnemy : public virtual ITargetSelector {
 public:
  TargetFirstEnemy(std::weak_ptr<ISelectableTarget> from) : from_(from) {}
  virtual ~TargetFirstEnemy() = default;

  std::vector<std::shared_ptr<ISelectableTarget>> getTargets() const override;

 private:
  std::weak_ptr<ISelectableTarget> from_;
};

class FixedTarget : public virtual ITargetSelector {
 public:
  FixedTarget(std::vector<std::weak_ptr<ISelectableTarget>> targets)
      : targets_(targets) {}
  virtual ~FixedTarget() = default;
  std::vector<std::shared_ptr<ISelectableTarget>> getTargets() const override {
    std::vector<std::shared_ptr<ISelectableTarget>> ret;
    for (const auto& target : targets_) {
      auto t = target.lock();
      if (t) {
        ret.push_back(t);
      }
    }
    return ret;
  }

 private:
  std::vector<std::weak_ptr<ISelectableTarget>> targets_;
};
