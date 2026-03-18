#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>
#include <stdexcept>

namespace XYZEngine
{
	enum class LogLevel
	{
		Debug,
		Info,
		Warning,
		Error,
		Fatal
	};

	class Logger
	{
	public:
		static Logger* Instance();

		void Init(const std::string& logFilePath);
		void Shutdown();

		void Log(LogLevel level, const std::string& message);
		void Debug(const std::string& message);
		void Info(const std::string& message);
		void Warning(const std::string& message);
		void Error(const std::string& message);
		void Fatal(const std::string& message);

		void SetMinLevel(LogLevel level);

	private:
		Logger() {}
		~Logger();

		Logger(Logger const&) = delete;
		Logger& operator=(Logger const&) = delete;

		LogLevel minLevel = LogLevel::Debug;
		std::ofstream logFile;
		bool initialized = false;

		std::string LevelToString(LogLevel level) const;
		std::string GetTimestamp() const;
	};

	class EngineException : public std::runtime_error
	{
	public:
		EngineException(const std::string& message)
			: std::runtime_error(message) {}
	};
}

#define XYZ_ASSERT(condition, message) \
	do { \
		if (!(condition)) { \
			XYZEngine::Logger::Instance()->Error( \
				std::string("ASSERT FAILED: ") + (message) + \
				" [" + __FILE__ + ":" + std::to_string(__LINE__) + "]"); \
		} \
	} while(0)
