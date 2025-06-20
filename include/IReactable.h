#pragma once

#include <functional>
#include <memory>
#include <vector>

class IAction;

class IReactable {
 public:
  virtual ~IReactable() = default;

  virtual std::vector<std::shared_ptr<IAction>> onAction(
      std::shared_ptr<IAction> action) = 0;
};
