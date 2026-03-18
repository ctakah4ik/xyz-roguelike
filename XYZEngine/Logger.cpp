#include "pch.h"
#include "Logger.h"

namespace XYZEngine
{
	Logger* Logger::Instance()
	{
		static Logger instance;
		return &instance;
	}

	Logger::~Logger()
	{
		Shutdown();
	}

	void Logger::Init(const std::string& logFilePath)
	{
		if (initialized)
		{
			return;
		}

		logFile.open(logFilePath, std::ios::out | std::ios::trunc);
		if (!logFile.is_open())
		{
			std::cerr << "[Logger] WARNING: Could not open log file: " << logFilePath << std::endl;
		}

		initialized = true;
		Info("Logger initialized. Log file: " + logFilePath);
	}

	void Logger::Shutdown()
	{
		if (initialized)
		{
			Info("Logger shutting down.");
			if (logFile.is_open())
			{
				logFile.close();
			}
			initialized = false;
		}
	}

	void Logger::Log(LogLevel level, const std::string& message)
	{
		if (level < minLevel)
		{
			return;
		}

		std::string timestamp = GetTimestamp();
		std::string levelStr = LevelToString(level);
		std::string formatted = "[" + timestamp + "] [" + levelStr + "] " + message;

		std::cout << formatted << std::endl;

		if (logFile.is_open())
		{
			logFile << formatted << std::endl;
			logFile.flush();
		}
	}

	void Logger::Debug(const std::string& message)
	{
		Log(LogLevel::Debug, message);
	}

	void Logger::Info(const std::string& message)
	{
		Log(LogLevel::Info, message);
	}

	void Logger::Warning(const std::string& message)
	{
		Log(LogLevel::Warning, message);
	}

	void Logger::Error(const std::string& message)
	{
		Log(LogLevel::Error, message);
	}

	void Logger::Fatal(const std::string& message)
	{
		Log(LogLevel::Fatal, message);
	}

	void Logger::SetMinLevel(LogLevel level)
	{
		minLevel = level;
	}

	std::string Logger::LevelToString(LogLevel level) const
	{
		switch (level)
		{
		case LogLevel::Debug:   return "DEBUG";
		case LogLevel::Info:    return "INFO";
		case LogLevel::Warning: return "WARNING";
		case LogLevel::Error:   return "ERROR";
		case LogLevel::Fatal:   return "FATAL";
		default:                return "UNKNOWN";
		}
	}

	std::string Logger::GetTimestamp() const
	{
		std::time_t now = std::time(nullptr);
		std::tm localTime;
		localtime_s(&localTime, &now);

		char buffer[32];
		std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &localTime);
		return std::string(buffer);
	}
}
