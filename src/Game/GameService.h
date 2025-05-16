#pragma once
#include "IGameService.h"
#define ADD_SERVICE(name)                                 \
 public:                                                  \
  void Add##name(I##name* service) { name##_ = service; } \
  void Remove##name() { name##_ = nullptr; }              \
  I##name* Get##name() { return name##_; }                \
                                                          \
 private:                                                 \
  I##name* name##_;

class GameService {
 public:
  static GameService& getInstance() {
    static GameService instance;
    return instance;
  }

  ADD_SERVICE(GameService)
};