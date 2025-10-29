// 属性网格
export const StatsGrid = ({ attack, defense }) => (
  <div className="stats-grid">
    <div className="stat-item">
      <div className="stat-value">{attack}</div>
      <div className="stat-label">攻击力</div>
    </div>
    <div className="stat-item">
      <div className="stat-value">{defense}</div>
      <div className="stat-label">防御力</div>
    </div>
  </div>
);