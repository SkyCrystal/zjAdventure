#pragma once

#include <memory>
#include <vector>

class IAction;

class IReactiable {
 public:
  virtual ~IReactiable() = default;

  virtual std::vector<std::unique_ptr<IAction>> onAction(
      std::unique_ptr<IAction> action) = 0;
};
