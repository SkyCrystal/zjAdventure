#include "Game.h"
#include "GameService.h"

#include "Action/Damage/NormalDamage.h"

#include "Util/Utils.h"

GAME_API Game::Game()
    : currentState(GameState::MENU), turnCount(0), isPlayerTurn(true) {
  // 初始化游戏数据
  gameData.playerHealth = 100;
  gameData.playerMaxHealth = 100;
  gameData.playerLevel = 1;
  gameData.playerExperience = 0;
  GameServiceManager::getInstance().AddGameService(this);
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
  NormalDamage* test;
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

int Game::getCurrentLevel() const {
  return 0;
}

int Game::getCurrentRound() const {
  return 0;
}

std::vector<std::shared_ptr<ICharacter>> Game::getCurrentCharacters() const {
  std::vector<std::shared_ptr<ICharacter>> result;
  for (auto& character : currentCharacters) {
    result.push_back(character);
  }
  return result;
}

std::shared_ptr<ICharacter> Game::getFirstEnemy(
    const std::shared_ptr<ICharacter>& me) const {
  if (is_different(currentEnemy, me)) {
    return currentEnemy.lock();
  }
  return currentPlayer.lock();
}
