#pragma once
// 目标选择器
#include <memory>
#include <vector>

class ISelectableTarget;

class ITargetSelector {
 public:
  virtual ~ITargetSelector() = default;

  virtual std::vector<std::shared_ptr<ISelectableTarget>> getTargets()
      const = 0;
};