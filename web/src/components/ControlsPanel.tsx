// 控制面板
export const ControlsPanel = ({ onNextTurn, onReset, isTurnDisabled, isGameEnded }) => (
  <div className="controls-panel">
    <div className="controls-title">游戏控制</div>
    <button
      className="action-button"
      onClick={onNextTurn}
      disabled={isTurnDisabled || isGameEnded}
    >
      {isGameEnded ? '游戏已结束' : (isTurnDisabled ? '处理中...' : '下一回合')}
    </button>
    <button
      className="action-button"
      onClick={onReset}
    >
      重置游戏
    </button>
  </div>
);