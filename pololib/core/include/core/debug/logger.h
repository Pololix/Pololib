#pragma once

#include <vector>
#include <string>

namespace plb
{
	enum class LogLevel
	{
		Debug = 0,
		Info,
		Warn,
		Error,
		Fatal
	};

	class Logger
	{
	public:
		Logger(const char* name);
		~Logger() = default;

		void setMinLevel(LogLevel level);
		void log(LogLevel level, const char* msg) const;

		const char* getName() const;
	private:
		const std::string m_Name;
		LogLevel m_MinLevel = LogLevel::Debug;
	};

	class LoggerManager
	{
	public:
		LoggerManager() = default;
		~LoggerManager() = default;

		static LoggerManager& get();

		void init();
		Logger& getLogger(const char* name);
	private:
		bool m_Init = false;
		Logger m_Logger = Logger("LoggerManager");

		std::vector<Logger> m_Loggers;
	};
}