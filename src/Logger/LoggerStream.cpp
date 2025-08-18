#include <spdlog/spdlog.h>
#include <cstdio>
#include "LoggerStream.h"
#include "Service/GameService.h"
#include "SpdLogger.h"

LogStream::LogStream(SpdLogger::Level level,
                     const char* file,
                     int line,
                     const char* function)
    : level_(level) {
  stream_ << "[" << file << ":" << line << "] " << function << " ";
}

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

  logger->log(static_cast<spdlog::level::level_enum>(level_), msg);
  logger->flush();
}

bool LogStream::should_log() const {
  return level_ >= GameServiceManager::getInstance().GetLogService()->getLevel();
}
