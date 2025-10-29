// 生命条
export const HealthBar = ({ current, max, type }) => {
  const percentage = (current / (max || 1)) * 100; // 防止除以0
  return (
    <div className="health-section">
      <div className="health-label">
        <span>生命值</span>
        <span><span>{current}</span>/<span>{max}</span></span>
      </div>
      <div className="health-bar">
        <div
          className={`health-fill ${type}`}
          style={{ width: `${percentage}%` }}
        ></div>
      </div>
    </div>
  );
};