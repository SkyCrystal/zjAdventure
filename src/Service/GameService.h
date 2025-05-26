#pragma once

#define ADD_SERVICE(name)                                 \
 public:                                                  \
  void Add##name(I##name* service) { name##_ = service; } \
  void Remove##name() { name##_ = nullptr; }              \
  I##name* Get##name() { return name##_; }                \
                                                          \
 private:                                                 \
  I##name* name##_;

class IGameService;

class GameServiceManager {
 public:
  static GameServiceManager& getInstance() {
    static GameServiceManager instance;
    return instance;
  }

  ADD_SERVICE(GameService)
};