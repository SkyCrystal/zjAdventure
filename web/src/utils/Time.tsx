export const getCurrentTime = () => {
  const now = new Date();
  return now.toLocaleTimeString('zh-CN', {
    hour12: false, hour: '2-digit', minute: '2-digit', second: '2-digit'
  });
}