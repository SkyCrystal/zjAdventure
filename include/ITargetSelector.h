#pragma once
// 目标选择器
#include <vector>

class ICharacter;

class ITargetSelector {
 public:
  virtual ~ITargetSelector() = default;

  virtual std::vector<ICharacter*> selectTargets() const = 0;
};