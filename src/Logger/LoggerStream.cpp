#include "LoggerStream.h"
#include <spdlog/spdlog.h>
#include "SpdLogger.h"
#include "Service/GameService.h"


LogStream::LogStream(SpdLogger::Level level, const char* file, int line)
    : level_(level), file_(file), line_(line) {}

LogStream::~LogStream() {
  if (should_log()) {
    log_message(stream_.str());
  }
}



void LogStream::log_message(const std::string& msg) {
  if (msg.empty())
    return;

  auto logger = GameServiceManager::getInstance().GetLogService()->getLogger();
  if (!logger)
    return;

  spdlog::source_loc loc{file_, line_, SPDLOG_FUNCTION};
  logger->log(loc, static_cast<spdlog::level::level_enum>(level_), msg);
}

bool LogStream::should_log() const {
  return level_ >= GameServiceManager::getInstance().GetLogService()->getLevel();
}
