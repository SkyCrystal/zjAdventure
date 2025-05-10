// 游戏状态更新函数
function updateGameState() {
  fetch('/api/game-state')
      .then(response => response.json())
      .then(data => {
        document.getElementById('player-level').textContent = data.player.level;
        document.getElementById('player-exp').textContent =
            data.player.experience;
        document.getElementById('player-health').textContent =
            data.player.health;
        document.getElementById('player-max-health').textContent =
            data.player.maxHealth;

        const healthPercentage =
            (data.player.health / data.player.maxHealth) * 100;
        document.getElementById('health-bar').style.width =
            `${healthPercentage}%`;
      })
      .catch(error => console.error('Error:', error));
}

// 定期更新游戏状态
function startGameStateUpdates() {
  // 立即更新一次
  updateGameState();
  // 每5秒更新一次
  setInterval(updateGameState, 1000);
}

// 当文档加载完成后启动更新
// 更新游戏状态
function updateGame() {
  fetch('/api/update')
      .then(data => {
        updateGameState();
      })
      .catch(error => console.error('Error:', error));
}

document.addEventListener('DOMContentLoaded', () => {
  startGameStateUpdates();
});