// 游戏状态管理
let gameData = null;
let lastActionCount = 0;

// 游戏状态映射
const GameState = {
  0: {name: '构建阶段', class: 'state-build'},
  1: {name: '战斗准备', class: 'state-before-battle'},
  2: {name: '战斗中', class: 'state-in-battle'},
  3: {name: '游戏结束', class: 'state-end'}
};

// 动作类型映射
const ActionType = {
  0: '未知',
  1: '外观效果',
  2: '伤害',
  3: '治疗',
  4: '受到伤害',
  5: '受到治疗',
  6: '临时增益',
  7: '永久增益',
  8: '移除增益',
  9: '移除道具',
  10: '添加道具',
  11: '战吼',
  12: '死亡',
  13: '游戏开始',
  14: '游戏结束',
  15: '回合开始',
  16: '回合结束',
  17: '行动开始',
  18: '行动结束',
  19: '移动'
};

// 更新游戏状态
function updateGameState() {
  fetch('/api/game-state')
      .then(response => response.json())
      .then(data => {
        gameData = data;
        updateUI(data);
      })
      .catch(error => {
        console.error('获取游戏状态失败:', error);
        showError('无法获取游戏状态');
      });
}

// 更新UI界面
function updateUI(data) {
  updateGameHeader(data);
  updateGameStateIndicator(data);
  updatePlayerCard(data.player);
  updateEnemyCard(data.enemy);
  updateActionsLog(data.actions_log_);
  updateControls(data);
}

// 更新游戏头部信息
function updateGameHeader(data) {
  document.getElementById('turn-count').textContent = data.turn_count_ || 0;
  document.getElementById('battle-round').textContent = data.battle_round_ || 0;
}

// 更新游戏状态指示器
function updateGameStateIndicator(data) {
  const indicator = document.getElementById('game-state-indicator');
  const state =
      GameState[data.state] || {name: '未知状态', class: 'state-unknown'};

  indicator.textContent = state.name;
  indicator.className = 'game-state-indicator ' + state.class;
}

// 更新玩家卡片
function updatePlayerCard(playerData) {
  if (!playerData) return;

  // 基本信息
  document.getElementById('player-id').textContent = playerData.index || '-';

  // 生命值 - 需要跟踪最大生命值
  const currentHealth = Math.max(0, playerData.health || 0);
  let maxHealth = parseInt(localStorage.getItem('player_max_health')) || 100;

  // 如果当前血量大于已知最大血量，更新最大血量
  if (currentHealth > maxHealth) {
    maxHealth = currentHealth;
    localStorage.setItem('player_max_health', maxHealth);
  }

  document.getElementById('player-health').textContent = currentHealth;
  document.getElementById('player-max-health').textContent = maxHealth;

  const healthPercentage = (currentHealth / maxHealth) * 100;
  document.getElementById('player-health-bar').style.width =
      `${healthPercentage}%`;

  // 战斗属性
  document.getElementById('player-attack').textContent =
      playerData.attackPower || 0;
  document.getElementById('player-defense').textContent =
      playerData.defensePower || 0;

  // 装备道具
  updateItems('player-items', playerData.items || []);

  // 死亡状态检查
  const playerCard = document.getElementById('player-card');
  if (currentHealth <= 0) {
    playerCard.style.opacity = '0.5';
    playerCard.style.filter = 'grayscale(100%)';
  } else {
    playerCard.style.opacity = '1';
    playerCard.style.filter = 'none';
  }
}

// 更新敌人卡片
function updateEnemyCard(enemyData) {
  if (!enemyData) return;

  // 基本信息
  document.getElementById('enemy-id').textContent = enemyData.index || '-';

  // 生命值 - 需要跟踪最大生命值
  const currentHealth = Math.max(0, enemyData.health || 0);
  let maxHealth = parseInt(localStorage.getItem('enemy_max_health')) || 100;

  // 如果当前血量大于已知最大血量，更新最大血量
  if (currentHealth > maxHealth) {
    maxHealth = currentHealth;
    localStorage.setItem('enemy_max_health', maxHealth);
  }

  document.getElementById('enemy-health').textContent = currentHealth;
  document.getElementById('enemy-max-health').textContent = maxHealth;

  const healthPercentage = (currentHealth / maxHealth) * 100;
  document.getElementById('enemy-health-bar').style.width =
      `${healthPercentage}%`;

  // 战斗属性
  document.getElementById('enemy-attack').textContent =
      enemyData.attackPower || 0;
  document.getElementById('enemy-defense').textContent =
      enemyData.defensePower || 0;

  // 装备道具
  updateItems('enemy-items', enemyData.items || []);

  // 死亡状态检查
  const enemyCard = document.getElementById('enemy-card');
  if (currentHealth <= 0) {
    enemyCard.style.opacity = '0.5';
    enemyCard.style.filter = 'grayscale(100%)';
  } else {
    enemyCard.style.opacity = '1';
    enemyCard.style.filter = 'none';
  }
}

// 更新道具列表
function updateItems(containerId, items) {
  const container = document.getElementById(containerId);
  container.innerHTML = '';

  if (!items || items.length === 0) {
    container.innerHTML =
        '<span style="opacity: 0.5; font-size: 0.8rem;">无装备</span>';
    return;
  }

  items.forEach(item => {
    const itemBadge = document.createElement('span');
    itemBadge.className = 'item-badge';
    itemBadge.textContent = getItemName(item);
    itemBadge.title = `ID: ${item.index} | 类型: ${item.targetType}`;
    container.appendChild(itemBadge);
  });
}

// 获取道具名称（这里可以根据实际需要扩展）
function getItemName(item) {
  // 可以根据item的index或其他属性来确定具体的道具名称
  return `道具#${item.index}`;
}

// 更新动作日志
function updateActionsLog(actionsLog) {
  if (!actionsLog || actionsLog.length === lastActionCount) return;

  const actionsList = document.getElementById('actions-list');

  // 只添加新的动作
  for (let i = lastActionCount; i < actionsLog.length; i++) {
    const action = actionsLog[i];
    const actionItem = createActionItem(action, i + 1);
    actionsList.appendChild(actionItem);
  }

  lastActionCount = actionsLog.length;

  // 自动滚动到底部
  const actionsContainer = document.querySelector('.actions-log');
  actionsContainer.scrollTop = actionsContainer.scrollHeight;
}

// 创建动作项元素
function createActionItem(action, index) {
  const actionItem = document.createElement('div');
  actionItem.className = 'action-item';

  // 根据动作类型设置样式
  const actionType = action.type || 0;
  if (actionType === 2)
    actionItem.classList.add('damage');
  else if (actionType === 4)
    actionItem.classList.add('hurt');
  else if (actionType === 12)
    actionItem.classList.add('death');

  const actionName = ActionType[actionType] || '未知动作';
  const actionDescription = getActionDescription(action);

  actionItem.innerHTML = `
        <div>#${index} ${actionName}</div>
        <div style="margin-top: 3px; font-size: 0.85rem; opacity: 0.9;">
            ${actionDescription}
        </div>
        <div class="action-time">${getCurrentTime()}</div>
    `;

  return actionItem;
}

// 获取动作描述
function getActionDescription(action) {
  const actionType = action.type || 0;
  const from = action.from ? action.from.description : '未知';

  switch (actionType) {
    case 2:  // 伤害
      return `来源: #${from} | 造成伤害`;
    case 4:  // 受到伤害
      return `目标受到伤害`;
    case 12:  // 死亡
      return `角色 #${from} 死亡`;
    case 13:  // 游戏开始
      return '战斗开始！';
    case 15:  // 回合开始
      return `第 ${action.data || '?'} 回合开始`;
    case 17:  // 行动开始
      return `角色 #${from} 开始行动`;
    default:
      return `执行了动作 (来源: #${from})`;
  }
}

// 获取当前时间
function getCurrentTime() {
  const now = new Date();
  return now.toLocaleTimeString(
      'zh-CN',
      {hour12: false, hour: '2-digit', minute: '2-digit', second: '2-digit'});
}

// 更新控制按钮状态
function updateControls(data) {
  const nextTurnBtn = document.getElementById('next-turn-btn');
  const resetBtn = document.getElementById('reset-btn');

  // 根据游戏状态启用/禁用按钮
  const gameState = data.state;

  if (gameState === 3) {  // 游戏结束
    nextTurnBtn.disabled = true;
    nextTurnBtn.textContent = '游戏已结束';
  } else {
    nextTurnBtn.disabled = false;
    nextTurnBtn.textContent = '下一回合';
  }

  resetBtn.disabled = false;
}

// 执行下一回合
function nextTurn() {
  const button = document.getElementById('next-turn-btn');
  button.disabled = true;
  button.textContent = '处理中...';

  fetch('/api/update')
      .then(response => {
        if (response.ok) {
          // 延迟一下再更新状态，确保后端处理完成
          setTimeout(updateGameState, 100);
        } else {
          throw new Error('更新失败');
        }
      })
      .catch(error => {
        console.error('更新游戏失败:', error);
        showError('更新游戏失败');
      })
      .finally(() => {
        setTimeout(() => {
          button.disabled = false;
          button.textContent = '下一回合';
        }, 500);
      });
}

// 重置游戏
function resetGame() {
  if (confirm('确定要重置游戏吗？这将清除所有进度。')) {
    // 清空本地状态
    gameData = null;
    lastActionCount = 0;

    // 清空本地存储的最大生命值
    localStorage.removeItem('player_max_health');
    localStorage.removeItem('enemy_max_health');

    // 清空动作日志显示
    document.getElementById('actions-list').innerHTML = '';

    // 这里可以添加重置游戏的API调用
    // 目前只是刷新页面
    location.reload();
  }
}

// 清空日志
function clearLog() {
  document.getElementById('actions-list').innerHTML = '';
  lastActionCount = 0;
}

// 显示错误信息
function showError(message) {
  const errorDiv = document.createElement('div');
  errorDiv.style.cssText = `
        position: fixed;
        top: 20px;
        left: 50%;
        transform: translateX(-50%);
        background: #e74c3c;
        color: white;
        padding: 10px 20px;
        border-radius: 5px;
        z-index: 1000;
        animation: fadeInOut 3s ease-in-out;
    `;
  errorDiv.textContent = message;
  document.body.appendChild(errorDiv);

  setTimeout(() => {
    if (errorDiv.parentNode) {
      errorDiv.parentNode.removeChild(errorDiv);
    }
  }, 3000);
}

// 添加淡入淡出动画
const style = document.createElement('style');
style.textContent = `
    @keyframes fadeInOut {
        0% { opacity: 0; transform: translateX(-50%) translateY(-20px); }
        20%, 80% { opacity: 1; transform: translateX(-50%) translateY(0); }
        100% { opacity: 0; transform: translateX(-50%) translateY(-20px); }
    }
`;
document.head.appendChild(style);

// 定期更新游戏状态
function startGameStateUpdates() {
  updateGameState();                   // 立即更新一次
  setInterval(updateGameState, 1000);  // 每1秒更新一次
}

// 页面加载完成后启动
document.addEventListener('DOMContentLoaded', () => {
  console.log('游戏界面已加载');
  startGameStateUpdates();

  // 添加键盘快捷键
  document.addEventListener('keydown', (e) => {
    if (e.key === ' ' || e.key === 'Enter') {  // 空格键或回车键
      e.preventDefault();
      nextTurn();
    } else if (e.key === 'r' || e.key === 'R') {  // R键重置
      e.preventDefault();
      resetGame();
    } else if (e.key === 'c' || e.key === 'C') {  // C键清空日志
      e.preventDefault();
      clearLog();
    }
  });
});

// 窗口聚焦时更新状态
window.addEventListener('focus', () => {
  updateGameState();
});

// 导出函数供HTML调用
window.nextTurn = nextTurn;
window.resetGame = resetGame;
window.clearLog = clearLog;