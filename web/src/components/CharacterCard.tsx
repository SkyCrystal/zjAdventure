import { HealthBar } from "./HealthBar";
import { StatsGrid } from "./StatsGrid";
import { ItemsSection } from "./ItemsSection";

export const CharacterCard = ({ characterData, type }) => {
  if (!characterData) {
    return (
      <div className={`character-card ${type}`} style={{ opacity: 0.5 }}>
        <div className="character-header">
          <div className="character-title">{type === 'player' ? '玩家' : '敌人'}</div>
          <div className="character-id">ID: <span>-</span></div>
        </div>

        <HealthBar current={0} max={100} type={type} />
        <StatsGrid attack={0} defense={0} />
        <ItemsSection items={[]} />
      </div>
    );
  }

  const { index, health = 0, maxHealth = 100, attackPower = 0, defensePower = 0, items = [] } = characterData;
  const currentHealth = Math.max(0, health);
  const isDead = currentHealth <= 0;

  return (
    <div
      className={`character-card ${type}`}
      style={{ opacity: isDead ? 0.5 : 1, filter: isDead ? 'grayscale(100%)' : 'none' }}
    >
      <div className="character-header">
        <div className="character-title">{type === 'player' ? '玩家' : '敌人'}</div>
        <div className="character-id">ID: <span>{index || '-'}</span></div>
      </div>

      <HealthBar current={currentHealth} max={maxHealth} type={type} />
      <StatsGrid attack={attackPower} defense={defensePower} />
      <ItemsSection items={items} />
    </div>
  );
};