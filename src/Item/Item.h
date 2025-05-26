#include "IItem.h"
#include "Utils.h"

class Item : public IItem {
 public:
  Item(std::weak_ptr<ISelectableTarget> owner) : owner_(owner) {}
  virtual ~Item() = default;
  virtual std::weak_ptr<ISelectableTarget> getOwner() const override {
    return owner_;
  }

 private:
  std::weak_ptr<ISelectableTarget> owner_;
};
