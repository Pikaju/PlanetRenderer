#include "Debug.h"

#include <iostream>

#include "Log.h"

void Debug::crash(const char* message)
{
	Log::log(message, LogType::ERROR);
	int k = 0;
	std::cin >> k;
}