export const getActionDescription = (action: any) => {
  const actionType = action.type || 0;
  const from = action.from ? action.from.description : '未知';
  switch (actionType) {
    case 2: return `${from} 发起攻击！`;
    case 4: return `目标受到伤害`;
    case 12: return `${from} 死亡！`;
    case 13: return '战斗开始！';
    case 15: return `第 ${action.data || '?'} 回合开始`;
    case 17: return `${from} 开始行动!`;
    default: return `执行了动作 (来源: #${from})`;
  }
}