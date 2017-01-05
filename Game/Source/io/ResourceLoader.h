#pragma once

#include <string>

class ResourceLoader
{
public:
	static bool readText(const char* file, std::string& destination);
};

