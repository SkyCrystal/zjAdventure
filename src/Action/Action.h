#pragma once

#include "IAction.h"

class Action : public IAction {
 public:
  Action(ActionType actionType, std::weak_ptr<ISelectableTarget> from)
      : IAction(actionType, from) {}
  virtual ~Action() = default;
};
