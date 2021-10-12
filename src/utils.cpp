/*
 * utils.cpp
 *
 * General utilities
 */

#include "utils.hpp"

int getNextID(int *tracker) {
	int r = *tracker;
	*tracker += 1;
	return r;
};
