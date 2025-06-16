#pragma once

#include <memory>
#include <nlohmann/json.hpp>

#include "IndexGenerator.h"

enum class TargetType {
  UNKNOWN,
  CHARACTER,
  ITEM,
  SYSTEM,
};

class ISelectableTarget
    : public std::enable_shared_from_this<ISelectableTarget> {
 public:
  ISelectableTarget(TargetType targetType, std::wstring description)
      : index_(GetNextIndex()),
        targetType_(targetType),
        description_(description) {}
  virtual ~ISelectableTarget() = default;
  virtual int getIndex() const { return index_; }
  virtual TargetType getTargetType() const { return targetType_; }
  virtual std::wstring getDescription() const { return description_; }
  virtual nlohmann::json toJson() const {
    nlohmann::json ret;
    ret["index"] = getIndex();
    ret["targetType"] = getTargetType();
    ret["description"] = getDescription();
    return ret;
  }

 private:
  int index_;
  TargetType targetType_;
  std::wstring description_;
};
