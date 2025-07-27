#pragma once
class LogStream;
class ILogService {
public:
  enum class Level { Trace, Debug, Info, Warn, Error, Critical };
  virtual LogStream LogStream(Level level, const char* file, int line) = 0;
};

#if defined(_MSC_VER)
#define LOG_FILE() __FILE__
#define LOG_LINE() __LINE__
#else
#define LOG_FILE() __builtin_FILE()
#define LOG_LINE() __builtin_LINE()
#endif

#define logT()                                                                           \
  GameServiceManager::getInstance().getLogService().LogStream(ILogService::Level::Trace, \
                                                              LOG_FILE(), LOG_LINE())
// #define logD() LogStream(Logger::Level::Debug, LOG_FILE(), LOG_LINE())
// #define logI() LogStream(Logger::Level::Info, LOG_FILE(), LOG_LINE())
// #define logW() LogStream(Logger::Level::Warn, LOG_FILE(), LOG_LINE())
// #define logE() LogStream(Logger::Level::Error, LOG_FILE(), LOG_LINE())
// #define logC() LogStream(Logger::Level::Critical, LOG_FILE(), LOG_LINE())