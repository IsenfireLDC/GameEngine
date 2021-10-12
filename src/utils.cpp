/*
 * utils.cpp
 *
 * General utilities
 */

#include "utils.hpp"

int Utils::nextID(int *tracker) {
	int r = *tracker;
	*tracker += 1;
	return r;
};
