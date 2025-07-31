#pragma once
#include <spdlog/spdlog.h>
#include <string>
#include "ILogService.h"
#include "LoggerStream.h"

class SpdLogger : public ILogService {
  
public:
  void init(const std::string& filename, Level autoLevel = Level::Info);
  virtual Level getLevel() override;
  virtual std::shared_ptr<spdlog::logger> getLogger() override;
  virtual LogStream Log(Level level, const char* file, int line) override;

private:
  std::shared_ptr<spdlog::logger> logger_;
  Level default_level_;
};
