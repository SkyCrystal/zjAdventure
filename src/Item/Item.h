#include "IItem.h"

class Item : public IItem {
 public:
  virtual ~Item() = default;
  virtual std::vector<std::shared_ptr<IAction>> onAction(
      std::shared_ptr<IAction> action) override;
};
