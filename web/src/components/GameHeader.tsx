export const GameHeader = ({ turnCount, battleRound }) => (
  <div className="game-header">
    <h1>回合制Roguelike战斗</h1>
    <div className="game-status">
      <div className="status-item">
        <span>回合: </span><span>{turnCount || 0}</span>
      </div>
      <div className="status-item">
        <span>战斗轮次: </span><span>{battleRound || 0}</span>
      </div>
    </div>
  </div>
);