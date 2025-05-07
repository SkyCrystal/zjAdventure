// 角色应当具有的基本能力
class ICharacter {
 public:
  virtual ~ICharacter() = default;
  virtual int getHealth() const = 0;
  virtual int getAttackPower() const = 0;
  virtual int getDefensePower() const = 0;
};