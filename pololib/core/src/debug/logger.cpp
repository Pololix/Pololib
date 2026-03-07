#include "core/debug/logger.h"

#include <iostream>
#include <algorithm>

namespace plb
{
	Logger::Logger(const char* name)
		: m_Name(name)
	{
		log(LogLevel::Info, "New logger created:");
		log(LogLevel::Info, name);
	}

	void Logger::setMinLevel(LogLevel level)
	{
		m_MinLevel = level;
	}

	//PLB_TODO: add fstream and other sinks, formatting...
	void Logger::log(LogLevel level, const char* msg) const
	{
		std::cout << msg << '\n';
	}

	const char* Logger::getName() const
	{
		return m_Name.c_str();
	}

	LoggerManager& LoggerManager::get()
	{
		static LoggerManager inst;
		return inst;
	}

	void LoggerManager::init()
	{
		if (m_Init)
		{
			m_Logger.log(LogLevel::Warn, "Tried to init LoggerManager more than once");
			return;
		}

		//else...
		m_Init = true;
	}

	Logger& LoggerManager::getLogger(const char* name)
	{
		if (!m_Init)
		{
			m_Logger.log(LogLevel::Error, "Tried to get logger without init LoggerManager");
			std::abort();
		}
		
		auto target = std::find_if(m_Loggers.begin(), m_Loggers.end(), [&name](const Logger& logger)
		{
			return logger.getName() == name;
		});

		if (target == m_Loggers.end())
		{
			return m_Loggers.emplace_back(name);
		}
		else
		{
			return (*target);
		}
	}
}