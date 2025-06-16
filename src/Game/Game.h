#pragma once

#include <memory>
#include <nlohmann/json.hpp>
#include <queue>
#include <string>
#include <vector>

#include "IAction.h"
#include "IGameService.h"
#include "ISelectableTarget.h"
#include "dllexport.h"

class Game : public IGameService, public ISelectableTarget {
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

  GameState getState() const { return current_state_; }

  nlohmann::json getGameStateJson() const;

 private:
  void onContinuePendingActions();
  std::vector<std::shared_ptr<ICharacter>> current_characters_;
  std::vector<std::weak_ptr<ICharacter>> current_enemies_;
  std::vector<std::weak_ptr<ICharacter>> current_players_;

  GameState current_state_;
  int battle_round_ = 0;
  int turn_count_ = 0;
  std::queue<std::shared_ptr<IAction>> pending_actions_;
  std::vector<nlohmann::json> actions_log_;
};