#pragma once
#include <concepts>
#include <random>

#include "ICharacter.h"
#include "ITargetSelector.h"

// template <typename T>
// concept RefedPtr = requires(T a) {
//   { a.owner_before(a) } -> std::convertible_to<bool>;
// };

std::shared_ptr<ICharacter> getOwner(std::shared_ptr<ISelectableTarget> target);

/**
 * 随机数发生器类
 * 提供生成0到指定范围整数的接口
 */
class RandomGenerator {
 private:
  /**
   * 构造函数，初始化随机数引擎
   */
  RandomGenerator() : engine_(std::random_device{}()) {}

 public:
  /**
   * 生成0到max之间的随机整数（包含0和max）
   * @param max 随机数的最大值（包含）
   * @return 0到max之间的随机整数
   */
  static int generateInt(int max) {
    if (max < 0) {
      return 0;
    }
    std::uniform_int_distribution<int> distribution(0, max);
    return distribution(instance_.engine_);
  }

  /**
   * 生成0到max-1之间的随机整数（包含0，不包含max）
   * @param max 随机数的最大值（不包含）
   * @return 0到max-1之间的随机整数
   */
  static int generateIntExclusive(int max) {
    if (max <= 0) {
      return 0;
    }
    std::uniform_int_distribution<int> distribution(0, max - 1);
    return distribution(instance_.engine_);
  }

  /**
   * 生成0.0到1.0之间的随机浮点数
   * @return 0.0到1.0之间的随机浮点数
   */
  static double generateDouble() {
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(instance_.engine_);
  }

  /**
   * @brief 成功率为rate%的检定
   */
  static bool check(int rate) { return generateIntExclusive(100) <= rate; }

 private:
  std::mt19937 engine_;  // Mersenne Twister随机数引擎
  static RandomGenerator instance_;
};

class TargetFirstEnemy : public virtual ITargetSelector {
 public:
  TargetFirstEnemy(std::weak_ptr<ISelectableTarget> from) : from_(from) {}
  virtual ~TargetFirstEnemy() = default;

  std::vector<std::shared_ptr<ISelectableTarget>> getTargets() const override;

 private:
  std::weak_ptr<ISelectableTarget> from_;
};

class FixedTarget : public virtual ITargetSelector {
 public:
  FixedTarget(std::vector<std::weak_ptr<ISelectableTarget>> targets)
      : targets_(targets) {}
  virtual ~FixedTarget() = default;
  std::vector<std::shared_ptr<ISelectableTarget>> getTargets() const override {
    std::vector<std::shared_ptr<ISelectableTarget>> ret;
    for (const auto& target : targets_) {
      auto t = target.lock();
      if (t) {
        ret.push_back(t);
      }
    }
    return ret;
  }

 private:
  std::vector<std::weak_ptr<ISelectableTarget>> targets_;
};
