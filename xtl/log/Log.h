#pragma once

#include "xtl/log/impl/Log.h"
#include "xtl/log/impl/LogStream.h"

#define XLOG(level) xtl::LogStream(__FILE__, __LINE__, level)

#define XLOG_DEBUG XLOG(xtl::Log::LogLevel::debug)
#define XLOG_INFO XLOG(xtl::Log::LogLevel::info)
#define XLOG_NOTICE XLOG(xtl::Log::LogLevel::notice)
#define XLOG_WARNING XLOG(xtl::Log::LogLevel::warning)
#define XLOG_FATAL XLOG(xtl::Log::LogLevel::fatal)

#define XLOG_SetLogId(id) xtl::Log::Instance()->SetLogId(id)
