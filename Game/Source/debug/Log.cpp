#include "Log.h"

#include <iostream>
#include <string>

void Log::log(const char* message, LogType::LogType type)
{
	std::string m(message);
	switch (type) {
	case LogType::INFO: m = "Info> " + m; break;
	case LogType::WARNING: m = "Warning> " + m; break;
	case LogType::ERROR: m = "Error> " + m; break;
	}
	std::cout << m << std::endl;
}