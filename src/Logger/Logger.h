#pragma once
#include "Service/GameService.h"
#include "Logger/LoggerStream.h"

#if defined(_MSC_VER)
#define LOG_FILE() __FILE__
#define LOG_LINE() __LINE__
#else
#define LOG_FILE() __builtin_FILE()
#define LOG_LINE() __builtin_LINE()
#endif

#define logT()                                                                                 \
  GameServiceManager::getInstance().getLogService().Log(ILogService::Level::Trace, LOG_FILE(), \
                                                        LOG_LINE())

#define logD()                                                                            \
  GameServiceManager::getInstance().getLogService().Log(Logger::Level::Debug, LOG_FILE(), \
                                                        LOG_LINE())
#define logI() \
  GameServiceManager::getInstance().getLogService().Log(Logger::Level::Info, LOG_FILE(), LOG_LINE())
#define logW() \
  GameServiceManager::getInstance().getLogService().Log(Logger::Level::Warn, LOG_FILE(), LOG_LINE())
#define logE()                                                                            \
  GameServiceManager::getInstance().getLogService().Log(Logger::Level::Error, LOG_FILE(), \
                                                        LOG_LINE())
#define logC()                                                                               \
  GameServiceManager::getInstance().getLogService().Log(Logger::Level::Critical, LOG_FILE(), \
                                                        LOG_LINE())