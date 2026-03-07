#pragma once
//PLB_TODO: add config file and conditional compilation
//			add variadic args for context info

#include "core/debug/logger.h"

#define PLB_LOG_DEBUG(logger, msg)	plb::LoggerManager::get().getLogger(logger).log(plb::LogLevel::Debug, msg)
#define PLB_LOG_INFO(logger, msg)	plb::LoggerManager::get().getLogger(logger).log(plb::LogLevel::Info, msg)
#define PLB_LOG_WARN(logger, msg)	plb::LoggerManager::get().getLogger(logger).log(plb::LogLevel::Warn, msg)
#define PLB_LOG_ERROR(logger, msg)	plb::LoggerManager::get().getLogger(logger).log(plb::LogLevel::Error, msg)
#define PLB_LOG_FATAL(logger, msg)	plb::LoggerManager::get().getLogger(logger).log(plb::LogLevel::Fatal, msg)