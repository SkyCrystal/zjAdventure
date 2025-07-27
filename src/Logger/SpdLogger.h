#pragma once
#include <spdlog/spdlog.h>
#include <string>
#include "ILogger.h"


#if defined(_MSC_VER)
#define LOG_FILE() __FILE__
#define LOG_LINE() __LINE__
#else
#define LOG_FILE() __builtin_FILE()
#define LOG_LINE() __builtin_LINE()
#endif
class LogStream;
class SpdLogger : public ILogger {
public:
  enum class Level { Trace, Debug, Info, Warn, Error, Critical };
  void init(const std::string& filename, Level autoLevel = Level::Info);
  Level getLevel();
  std::shared_ptr<spdlog::logger> getLogger();

private:
  std::shared_ptr<spdlog::logger> logger_;
  Level default_level_;
};

#define logT() LogStream(Logger::Level::Trace, LOG_FILE(), LOG_LINE())
#define logD() LogStream(Logger::Level::Debug, LOG_FILE(), LOG_LINE())
#define logI() LogStream(Logger::Level::Info, LOG_FILE(), LOG_LINE())
#define logW() LogStream(Logger::Level::Warn, LOG_FILE(), LOG_LINE())
#define logE() LogStream(Logger::Level::Error, LOG_FILE(), LOG_LINE())
#define logC() LogStream(Logger::Level::Critical, LOG_FILE(), LOG_LINE())