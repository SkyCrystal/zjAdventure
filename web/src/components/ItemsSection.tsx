import { getItemName } from "../utils";


// 道具部分
export const ItemsSection = ({ items }) => (
  <div className="items-section">
    <div className="items-title">装备道具</div>
    <div className="items-list">
      {(!items || items.length === 0) ? (
        <span style={{ opacity: 0.5, fontSize: '0.8rem' }}>无装备</span>
      ) : (
        items.map((item, i) => (
          <span key={i} className="item-badge" title={`ID: ${item.index} | 类型: ${item.targetType}`}>
            {getItemName(item)}
          </span>
        ))
      )}
    </div>
  </div>
);