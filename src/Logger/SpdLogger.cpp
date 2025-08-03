#include "SpdLogger.h"
#include <spdlog/common.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <iostream>
#include "LoggerStream.h"

void SpdLogger::init(const std::string& filename, Level autolevel) {
  logger_ = spdlog::basic_logger_mt("basic_logger", filename);
  logger_->flush_on(spdlog::level::trace);
  logger_->log(spdlog::level::err, "Hello, {}!", "world");
}

SpdLogger::Level SpdLogger::getLevel() {
  return default_level_;
}

std::shared_ptr<spdlog::logger> SpdLogger::getLogger() {
  return logger_;
}

LogStream SpdLogger::Log(SpdLogger::Level level, const char* file, int line, const char* function) {
  return LogStream(level, file, line, function);
}