import React from 'react';
import { getActionDescription, getCurrentTime } from '../utils';

// 动作日志 (使用 React.forwardRef 来接收 ref)
export const ActionsLog = React.forwardRef(({ actions, onClearLog }, ref) => (
    <div className="actions-log" ref={ref}> {/* 将 ref 附加到可滚动的元素 */}
        <div className="actions-title">
            <span>战斗日志</span>
            <button
                style={{ background: 'none', border: '1px solid rgba(255,255,255,0.3)', color: 'white', padding: '5px 10px', borderRadius: '5px', cursor: 'pointer' }}
                onClick={onClearLog}
            >
                清空
            </button>
        </div>
        <div className="actions-list" id="actions-list">
            {actions.map((action, index) => (
                <ActionItem
                    key={index} // 注意：这里使用 index 作为 key，仅在日志只增不删时安全
                    action={action}
                    index={index + 1} // 保持 1-based 索引
                />
            ))}
        </div>
    </div>
));

// 单个日志项
export const ActionItem = ({ action, index }) => {
    const actionType = action.type || 0;
    const actionName = ActionType[actionType] || '未知动作';
    const actionDescription = getActionDescription(action);

    let className = 'action-item';
    if (actionType === 2) className += ' damage';
    else if (actionType === 4) className += ' hurt';
    else if (actionType === 12) className += ' death';

    return (
        <div className={className}>
            <div>#{index} {actionName}</div>
            <div style={{ marginTop: '3px', fontSize: '0.85rem', opacity: 0.9 }}>
                {actionDescription}
            </div>
            <div className="action-time">{getCurrentTime()}</div>
        </div>
    );
};