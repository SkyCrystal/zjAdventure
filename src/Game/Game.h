#pragma once

#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "IGameService.h"
#include "dllexport.h"

class GAME_API Game : public IGameService {
 public:
  Game();
  ~Game();

  int getCurrentLevel() const override;
  int getCurrentRound() const override;
  std::vector<std::shared_ptr<ICharacter>> getCurrentCharacters()
      const override;
  std::shared_ptr<ICharacter> getFirstEnemy(
      const std::shared_ptr<ICharacter>& me) const override;

  enum class GameState { MENU, PLAYING, PAUSED, GAME_OVER };

  void update();

  GameState getState() const { return currentState; }

  nlohmann::json getGameStateJson() const;

 protected:
  std::vector<std::shared_ptr<ICharacter>> currentCharacters;
  std::weak_ptr<ICharacter> currentEnemy;
  std::weak_ptr<ICharacter> currentPlayer;

  GameState currentState;
  int turnCount;
  bool isPlayerTurn;

  struct GameData {
    int playerHealth;
    int playerMaxHealth;
    int playerLevel;
    int playerExperience;

  } gameData;
};