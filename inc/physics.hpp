#ifndef _PHYSICS_HPP_
#define _PHYSICS_HPP_

#include "update.hpp"

class PhysicsUpdate {
public:
	// Maximum calculations for a single physics tick
	static int maxIter = 10;

	// Perform a physics tick
	void update(float);
};

class Physics {
public:
	friend PhysicsUpdate;

	Physics(class Level*);
	virtual ~Physics();

	/*
	 * Set up variables, calculate movement
	 */
	virtual void physicsSetup(float) = 0;

	/*
	 * Calculate interactions, update state
	 * Returns true if calculations completed
	 */
	virtual bool physicsCalculate(float) = 0;

protected:
	class Level *level;

private:
	static std::unordered_map<class Level*, std::unordered_set<Physics*>> members;
};

#endif
