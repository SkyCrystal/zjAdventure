import { useState, useEffect, useCallback, useRef } from 'react';
import { initialGameData } from './consts';
import { CharacterCard, GameHeader, ActionsLog, GameStateIndicator, ControlsPanel } from './components';
import './App.css';


function App() {
  const [gameData, setGameData] = useState(initialGameData);
  const [isLoadingTurn, setIsLoadingTurn] = useState(false);
  const [error, setError] = useState(null);
  const [clearedLogCount, setClearedLogCount] = useState(0);
  const logContainerRef = useRef(null);

  const updateGameState = useCallback(async () => {
    try {
      const response = await fetch('/api/game-state');
      if (!response.ok) throw new Error('网络响应失败');
      const data = await response.json();
      setGameData(data);
      setError(null); // 成功后清除错误
    } catch (err) {
      console.error('获取游戏状态失败:', err);
      setError('无法获取游戏状态');
    }
  }, []);

  useEffect(() => {
    updateGameState();
    const intervalId = setInterval(updateGameState, 1000);

    const handleFocus = () => updateGameState();
    window.addEventListener('focus', handleFocus);

    return () => {
      clearInterval(intervalId);
      window.removeEventListener('focus', handleFocus);
    };
  }, [updateGameState]);

  const handleNextTurn = useCallback(async () => {
    if (isLoadingTurn || gameData?.state === 3) return;

    setIsLoadingTurn(true);
    try {
      const response = await fetch('/api/update');
      if (!response.ok) throw new Error('更新失败');
      // 延迟一下再更新状态，确保后端处理完成
      setTimeout(updateGameState, 100);
    } catch (err) {
      console.error('更新游戏失败:', err);
      setError('更新游戏失败');
    } finally {
      // 模拟原版JS的延迟
      setTimeout(() => setIsLoadingTurn(false), 500);
    }
  }, [isLoadingTurn, gameData, updateGameState]); // 依赖项

  const handleResetGame = useCallback(() => {
    if (window.confirm('确定要重置游戏吗？这将清除所有进度。')) {
      // 原版逻辑是重新加载页面
      location.reload();
    }
  }, []); // 无依赖

  const handleClearLog = useCallback(() => {
    // 不修改 gameData，而是记录清空时日志的数量
    // 下次渲染时，只显示此数量之后的新日志
    setClearedLogCount(gameData?.actions_log_?.length || 0);
  }, [gameData]); // 依赖 gameData

  // --- Effect: 键盘快捷键 ---
  useEffect(() => {
    const handleKeyDown = (e) => {
      if (e.target.tagName === 'INPUT' || e.target.tagName === 'TEXTAREA') return;

      if (e.key === ' ' || e.key === 'Enter') {
        e.preventDefault();
        handleNextTurn();
      } else if (e.key === 'r' || e.key === 'R') {
        e.preventDefault();
        handleResetGame();
      } else if (e.key === 'c' || e.key === 'C') {
        e.preventDefault();
        handleClearLog();
      }
    };
    document.addEventListener('keydown', handleKeyDown);
    return () => document.removeEventListener('keydown', handleKeyDown);
  }, [handleNextTurn, handleResetGame, handleClearLog]); // 依赖处理器

  // --- Effect: 自动滚动日志 ---
  useEffect(() => {
    if (logContainerRef.current) {
      const { scrollHeight, clientHeight } = logContainerRef.current;
      logContainerRef.current.scrollTop = scrollHeight - clientHeight;
    }
  }, [gameData?.actions_log_]);


  const { players, enemies, turn_count_, battle_round_, state, actions_log_ } = gameData;
  // players[0] 可能会是 undefined, CharacterCard 组件会处理这个
  const player = players ? players[0] : null;
  const enemy = enemies ? enemies[0] : null;
  const isGameEnded = state === 3;

  // 只显示被清空之后的新日志
  const displayedLogs = actions_log_?.slice(clearedLogCount) || [];

  return (
    <div className="game-container">
      {error && <ShowError message={error} />}

      <GameStateIndicator stateCode={state} />

      <GameHeader
        turnCount={turn_count_}
        battleRound={battle_round_}
      />

      <Battlefield player={player} enemy={enemy} />

      <ControlsPanel
        onNextTurn={handleNextTurn}
        onReset={handleResetGame}
        isTurnDisabled={isLoadingTurn}
        isGameEnded={isGameEnded}
      />

      <ActionsLog
        ref={logContainerRef} // 传递 ref
        actions={displayedLogs}
        onClearLog={handleClearLog}
      />
    </div>
  );
}

const ShowError = ({ message }) => {
  const [visible, setVisible] = useState(true);

  useEffect(() => {
    const timer = setTimeout(() => setVisible(false), 3000);
    return () => clearTimeout(timer);
  }, []);

  if (!visible) return null;
  return <div className="error-popup">{message}</div>;
};

const Battlefield = ({ player, enemy }) => (
  <div className="battlefield">
    <CharacterCard characterData={player} type="player" />
    <div className="vs-indicator">VS</div>
    <CharacterCard characterData={enemy} type="enemy" />
  </div>
);

export default App;