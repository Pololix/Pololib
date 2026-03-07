#pragma once

//PLB_TODO: remove large header (cstdlib) from comon .h
//			track file, script, etc

#include <cstdlib> //this
#include "core/debug/logger.h"

#ifdef PLB_BUILD_DEBUG
#define PLB_DEBUG_ASSERT(cond, msg)\
	do\
	{\
		if (!(cond))\
		{\
			plb::LoggerManager::get().getLogger("Program").log(plb::LogLevel::Fatal, msg);\
			std::abort();\
		}\
	} while (0)
#else
#define PLB_DEBUG_ASSERT(cond, msg) ((void)0)
#endif

#define PLB_ASSERT(cond, msg)\
	do\
	{\
		if (!(cond))\
		{\
			plb::LoggerManager::get().getLogger("Program").log(plb::LogLevel::Fatal, msg);\
			std::abort();\
		}\
	} while (0)