#pragma once
#include "Logger/LoggerStream.h"
#include "Service/GameService.h"

#if defined(_MSC_VER)
#define LOG_FILE() (__FILE__ + SOURCE_PATH_OFFSET)
#define LOG_LINE() __LINE__
#define LOG_FUNCTION() __FUNCSIG__
#else
#define LOG_FILE() (__builtin_FILE() + SOURCE_PATH_OFFSET)
#define LOG_LINE() __builtin_LINE()
#define LOG_FUNCTION() __PRETTY_FUNCTION__
#endif

#define logT()                                            \
                                                          \
  GameServiceManager::getInstance().GetLogService()->Log( \
      ILogService::Level::Trace, LOG_FILE(), LOG_LINE(), LOG_FUNCTION())

#define logD()                                            \
                                                          \
  GameServiceManager::getInstance().GetLogService()->Log( \
      ILogService::Level::Debug, LOG_FILE(), LOG_LINE(), LOG_FUNCTION())

#define logI()                                            \
                                                          \
  GameServiceManager::getInstance().GetLogService()->Log( \
      ILogService::Level::Info, LOG_FILE(), LOG_LINE(), LOG_FUNCTION())

#define logW()                                            \
                                                          \
  GameServiceManager::getInstance().GetLogService()->Log( \
      ILogService::Level::Warn, LOG_FILE(), LOG_LINE(), LOG_FUNCTION())

#define logE()                                            \
                                                          \
  GameServiceManager::getInstance().GetLogService()->Log( \
      ILogService::Level::Error, LOG_FILE(), LOG_LINE(), LOG_FUNCTION())

#define logC()                                            \
                                                          \
  GameServiceManager::getInstance().GetLogService()->Log( \
      ILogService::Level::Critical, LOG_FILE(), LOG_LINE(), LOG_FUNCTION())
