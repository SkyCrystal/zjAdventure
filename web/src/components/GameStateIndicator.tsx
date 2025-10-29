import { GameState } from "../consts";

// 游戏状态指示器
export const GameStateIndicator = ({ stateCode }) => {
  const state = GameState[stateCode] || { name: '未知状态', class: 'state-unknown' };
  return (
    <div className={`game-state-indicator ${state.class}`}>
      {state.name}
    </div>
  );
};