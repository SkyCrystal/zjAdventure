#pragma once
#include <spdlog/spdlog.h>
#include <string>
#include "ILogService.h"

class LogStream;
class SpdLogger : public ILogService {
public:
  void init(const std::string& filename, Level autoLevel = Level::Info);
  Level getLevel();
  std::shared_ptr<spdlog::logger> getLogger();

private:
  std::shared_ptr<spdlog::logger> logger_;
  Level default_level_;
};
