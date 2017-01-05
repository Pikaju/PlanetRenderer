#pragma once

namespace LogType
{
	enum LogType
	{
		INFO, WARNING, ERROR
	};
}

class Log
{
public:
	static void log(const char* message, LogType::LogType type = LogType::INFO);
};

