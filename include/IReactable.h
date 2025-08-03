#pragma once

#include <functional>
#include <memory>
#include <vector>

class IAction;

class IReactable {
 public:
  virtual ~IReactable() = default;

  virtual void onAction(std::shared_ptr<IAction> action) = 0;
};
