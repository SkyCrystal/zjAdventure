#pragma once

#include "IndexGenerator.h"

enum class TargetType {
  UNKNOWN,
  CHARACTER,
  ITEM,
  SYSTEM,
};

class ISelectableTarget {
 public:
  ISelectableTarget(TargetType targetType)
      : index_(GetNextIndex()), targetType_(targetType) {}
  virtual ~ISelectableTarget() = default;
  virtual int getIndex() const { return index_; }
  virtual TargetType getTargetType() const { return targetType_; }

 private:
  int index_;
  TargetType targetType_;
};
