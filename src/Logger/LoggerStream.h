#pragma once
#include <spdlog/spdlog.h>
#include <sstream>
#include "SpdLogger.h"

class LogStream {
public:
  LogStream(SpdLogger::Level level, const char* file, int line);
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

  SpdLogger::Level level_;
  std::ostringstream stream_;
  const char* file_;
  int line_;
};
