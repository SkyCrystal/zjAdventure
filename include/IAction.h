// 各种动作
class IAction {
 public:
  virtual ~IAction() = default;
  virtual void OnAction();
};