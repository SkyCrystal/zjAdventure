#include "Game.h"

GAME_API Game::Game()
    : currentState(GameState::MENU), turnCount(0), isPlayerTurn(true) {
  // 初始化游戏数据
  gameData.playerHealth = 100;
  gameData.playerMaxHealth = 100;
  gameData.playerLevel = 1;
  gameData.playerExperience = 0;
}

GAME_API Game::~Game() {
  // 清理资源
}

GAME_API void Game::update() {
  gameData.playerExperience += 1;
  if (currentState != GameState::PLAYING) {
    return;
  }

  // 游戏逻辑更新
  if (isPlayerTurn) {
    // 处理玩家回合
  } else {
    // 处理敌人回合
  }
}

GAME_API nlohmann::json Game::getGameStateJson() const {
  nlohmann::json j;
  j["state"] = static_cast<int>(currentState);
  j["turnCount"] = turnCount;
  j["isPlayerTurn"] = isPlayerTurn;

  // 添加玩家数据
  j["player"] = {{"health", gameData.playerHealth},
                 {"maxHealth", gameData.playerMaxHealth},
                 {"level", gameData.playerLevel},
                 {"experience", gameData.playerExperience}};

  return j;
}