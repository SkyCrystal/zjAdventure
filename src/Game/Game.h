#pragma once

#include <memory>
#include <nlohmann/json.hpp>
#include <queue>
#include <string>
#include <vector>

#include "IAction.h"
#include "IGameService.h"
#include "dllexport.h"

class Game : public IGameService {
 public:
  Game();
  ~Game();

  int getCurrentLevel() const override;
  int getCurrentRound() const override;
  std::vector<std::shared_ptr<ICharacter>> getCurrentCharacters()
      const override;
  std::shared_ptr<ICharacter> getFirstEnemy(
      const std::shared_ptr<ICharacter>& me) const override;

  enum class GameState { BUILD, BEFORE_BATTLE, IN_BATTLE, END };

  void update();

  GameState getState() const { return currentState; }

  nlohmann::json getGameStateJson() const;

 private:
  void onContinuePendingActions();
  std::vector<std::shared_ptr<ICharacter>> current_characters_;
  std::weak_ptr<ICharacter> current_enemy_;
  std::weak_ptr<ICharacter> current_player_;

  GameState currentState;
  int turnCount;
  bool isPlayerTurn;
  std::queue<std::shared_ptr<IAction>> pending_actions_;
  std::vector<std::shared_ptr<IAction>> actions_log_;
};