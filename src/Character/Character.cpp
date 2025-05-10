#include "Character.h"

Character::Character(int health,
                     int attackPower,
                     int defensePower,
                     bool isEnemy) {
  health_ = health;
  attackPower_ = attackPower;
  defensePower_ = defensePower;
  isEnemy_ = isEnemy;
}
