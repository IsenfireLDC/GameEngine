/*
 * utils.hpp
 *
 * General utilities used throughout the program
 */

#ifndef _UTILS_H_
#define _UTILS_H_

#include <string>

struct Utils {
	static int nextID(int*);
	
	static void create_directories(std::string);
};

#endif
