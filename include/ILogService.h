#pragma once
#include <memory>

class LogStream;
namespace spdlog {
class logger;
}
class ILogService {
public:
  enum class Level { Trace, Debug, Info, Warn, Error, Critical };
  virtual LogStream Log(Level level, const char* file, int line) = 0;
  virtual std::shared_ptr<spdlog::logger> getLogger() = 0;
  virtual Level getLevel() = 0;
};
