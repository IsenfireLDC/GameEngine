/*
 * utils.cpp
 *
 * General utilities
 */

#include "utils.hpp"

//#include <sys/stat.h>
//#include <direct.h> //Thanks, windows
#include <fileapi.h>

int Utils::nextID(int *tracker) {
	int r = *tracker;
	*tracker += 1;
	return r;
};

void Utils::create_directories(std::string path) {
	size_t pos = 0;

	while(pos != std::string::npos) {
		pos = path.find("/", pos+1);
		CreateDirectoryA(path.substr(0, pos).c_str(), nullptr);
	};
};
