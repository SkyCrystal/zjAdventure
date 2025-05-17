#pragma once
#include <concepts>

#include "ICharacter.h"
#include "ITargetSelector.h"

template <typename T>
concept RefedPtr = requires(T a) {
                     { a.owner_before(a) } -> std::convertible_to<bool>;
                   };

template <RefedPtr T, RefedPtr U>

bool is_different(T&& t, U&& u) {
  return t.owner_before(u) || u.owner_before(t);
}
std::weak_ptr<ICharacter> getOwner(std::weak_ptr<ISelectableTarget> target);

class TargetFirstEnemy : public virtual ITargetSelector {
 public:
  TargetFirstEnemy(std::weak_ptr<ISelectableTarget> from) : from_(from) {}
  virtual ~TargetFirstEnemy() = default;

  std::vector<std::weak_ptr<ISelectableTarget>> getTargets() const override;

 private:
  std::weak_ptr<ISelectableTarget> from_;
};
