#pragma once

#include <map>
#include <memory>

#include "Action/Actions.h"
#include "ICharacter.h"

// #include "Item/Attack/NormalAttack.h"

std::shared_ptr<AddItemAction> CreateAddItemAction(
    std::shared_ptr<ISelectableTarget> from,
    std::shared_ptr<IItem> item);

struct Context {
  int intdata1;
  int intdata2;
  std::string strdata;
};

class ItemConstructorImpl;
class ItemConstructor {
 public:
  ItemConstructor() : impl_(nullptr) {}
  ItemConstructor(std::shared_ptr<ItemConstructorImpl> impl) : impl_(impl) {}
  ItemConstructor(ItemConstructor&& other) : impl_(std::move(other.impl_)) {}
  ItemConstructor& operator=(ItemConstructor&& other) {
    impl_ = std::move(other.impl_);
    return *this;
  }
  std::shared_ptr<IItem> operator()(std::shared_ptr<ICharacter> owner,
                                    const Context& context);

 private:
  std::shared_ptr<ItemConstructorImpl> impl_;
};

class ItemManager {
 public:
  static ItemManager* getInstance();
  std::shared_ptr<IItem> MakeItem(const std::string& itemName,
                                  std::shared_ptr<ICharacter> owner,
                                  const Context& context);

 private:
  ItemManager();
  std::map<std::string, ItemConstructor> item_constructors_;
};
