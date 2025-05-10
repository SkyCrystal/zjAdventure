#pragma once

#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "dllexport.h"

class GAME_API Game {
 public:
  Game();
  ~Game();

  // 游戏状态
  enum class GameState { MENU, PLAYING, PAUSED, GAME_OVER };

  // 游戏主循环
  void update();

  // 获取游戏状态
  GameState getState() const { return currentState; }

  // 获取游戏数据的JSON表示
  nlohmann::json getGameStateJson() const;

 protected:
  GameState currentState;
  int turnCount;
  bool isPlayerTurn;

  // 游戏数据
  struct GameData {
    int playerHealth;
    int playerMaxHealth;
    int playerLevel;
    int playerExperience;
    // 可以添加更多游戏数据
  } gameData;
};