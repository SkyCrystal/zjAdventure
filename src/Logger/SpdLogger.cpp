#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <iostream>
#include "LoggerStream.h"
#include "SpdLogger.h"


void SpdLogger::init(const std::string& filename, Level autolevel) {
  try {
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(filename, true);

    std::vector<spdlog::sink_ptr> sinks{console_sink, file_sink};
    auto new_logger_ = std::make_shared<spdlog::logger>("main", sinks.begin(), sinks.end());

    new_logger_->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%-7l%$] [%s:%#] %v");
    new_logger_->set_level(static_cast<spdlog::level::level_enum>(autolevel));
    new_logger_->flush_on(static_cast<spdlog::level::level_enum>(Level::Warn));
    logger_ = new_logger_;
  } catch (const spdlog::spdlog_ex& ex) {
    std::cerr << "Log init failed: " << ex.what() << std::endl;
    logger_ = spdlog::stdout_color_mt("fallback");
  }
}

SpdLogger::Level SpdLogger::getLevel() {
  return default_level_;
}

std::shared_ptr<spdlog::logger> SpdLogger::getLogger() {
  return logger_;
}
