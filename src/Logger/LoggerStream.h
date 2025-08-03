#pragma once
#include <spdlog/spdlog.h>
#include <sstream>
#include "ILogService.h"

class LogStream {
public:
  LogStream(ILogService::Level level, const char* file, int line, const char* function);
  ~LogStream();

  // 流操作符重载

  template <typename T>
  LogStream& operator<<(const T& value) {
    if (should_log()) {
      stream_ << value;
    }
    return *this;
  }

private:
  void log_message(const std::string& msg);
  bool should_log() const;

  ILogService::Level level_;
  std::ostringstream stream_;
};
