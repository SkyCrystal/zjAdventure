#include <spdlog/spdlog.h>
#include <cstdio>
#include "LoggerStream.h"
#include "Service/GameService.h"
#include "SpdLogger.h"


LogStream::LogStream(SpdLogger::Level level, const char* file, int line)
    : level_(level), file_(file), line_(line) {}

LogStream::~LogStream() {
  if (should_log()) {
    log_message(stream_.str());
  }
}

void LogStream::log_message(const std::string& msg) {
  if (msg.empty()) {
    printf("ERROR: Log is empty");
    return;
  }

  auto logger = GameServiceManager::getInstance().GetLogService()->getLogger();
  if (!logger) {
    printf("ERROR: No logger");
    return;
  }

  spdlog::source_loc loc{file_, line_, SPDLOG_FUNCTION};
  logger->log(loc, static_cast<spdlog::level::level_enum>(level_), msg);
  logger->log(static_cast<spdlog::level::level_enum>(level_), msg);
  logger->log(spdlog::level::err, msg.c_str());
  logger->flush();
}

bool LogStream::should_log() const {
  return level_ >= GameServiceManager::getInstance().GetLogService()->getLevel();
}
