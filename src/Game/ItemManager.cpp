#include "ItemManager.h"

#include <memory>
#include <utility>

#include "IItem.h"
#include "Item/Attack/NormalAttack.h"
#include "Service/GameService.h"

namespace {
using CreateItemFunction =
    std::function<std::shared_ptr<IItem>(std::shared_ptr<ICharacter>,
                                         const Context&)>;

template <typename T, typename... Args>
  requires std::is_base_of_v<IItem, T>
std::shared_ptr<IItem> CreateItem(Args&&... args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

// 模板函数：接受参数包Args，将每个Arg::get()的返回值作为参数传递给CreateItem
template <typename T, typename... Args>
  requires std::is_base_of_v<IItem, T> && requires(Args... args) {
    {
      T(std::declval<std::shared_ptr<ICharacter>>(),
        std::forward<Args>(args)...)
    };
  }
std::shared_ptr<IItem> CreateItemWithContext(std::shared_ptr<ICharacter> owner,
                                             const Context& context) {
  return CreateItem<T>(owner, Args::Get(context)...);
}
}  // namespace

class ItemConstructorImpl {
 public:
  explicit ItemConstructorImpl(CreateItemFunction constructor)
      : constructor_(std::move(constructor)) {}

  template <typename T, typename... Args>
  static std::shared_ptr<ItemConstructorImpl> make() {
    return std::make_shared<ItemConstructorImpl>(
        [](std::shared_ptr<ICharacter> owner, const Context& context) {
          return CreateItemWithContext<T, Args...>(std::move(owner), context);
        });
  }

  std::shared_ptr<IItem> operator()(std::shared_ptr<ICharacter> owner,
                                    const Context& context) {
    return constructor_(std::move(owner), context);
  }

 private:
  CreateItemFunction constructor_;
};

std::shared_ptr<IItem> ItemConstructor::operator()(
    std::shared_ptr<ICharacter> owner,
    const Context& context) {
  return impl_->operator()(std::move(owner), context);
}

template <auto Context::* member_ptr>
class From {
 public:
  static auto Get(const Context& context) -> decltype(context.*member_ptr) {
    return context.*member_ptr;
  }
};

ItemManager::ItemManager() {
  item_constructors_["NormalAttack"] =
      ItemConstructorImpl::make<NormalAttack>();
}

ItemManager* ItemManager::getInstance() {
  static ItemManager instance;
  return &instance;
}

std::shared_ptr<IItem> ItemManager::MakeItem(const std::string& itemName,
                                             std::shared_ptr<ICharacter> owner,
                                             const Context& context) {
  if (item_constructors_.find(itemName) == item_constructors_.end()) {
    throw std::runtime_error("Item " + itemName + " not found");
  }

  return item_constructors_[itemName](std::move(owner), context);
}

std::shared_ptr<AddItemAction> ItemManager::MakeAddItemAction(
    std::shared_ptr<ISelectableTarget> from,
    const std::string& itemName,
    std::shared_ptr<ICharacter> owner,
    const Context& context) {
  return std::make_shared<AddItemAction>(std::move(from),
                                         MakeItem(itemName, owner, context));
}

void ItemManager::PostAddItemAction(std::shared_ptr<ISelectableTarget> from,
                                    const std::string& itemName,
                                    std::shared_ptr<ICharacter> owner,
                                    const Context& context) {
  auto addItemAction = MakeAddItemAction(from, itemName, owner, context);
  GameServiceManager::getInstance().GetGameService()->postPendingAction(
      addItemAction);
}
