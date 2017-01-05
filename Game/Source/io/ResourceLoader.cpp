#include "ResourceLoader.h"

#include <fstream>

bool ResourceLoader::readText(const char* file, std::string& destination)
{
	std::ifstream in;
	in.open(file);
	if (!in.is_open()) return false;

	std::string line;
	while (!in.eof()) {
		std::getline(in, line);
		destination += line + "\n";
	}

	return true;
}