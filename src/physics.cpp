#include "physics.hpp"


void PhysicsUpdate::update(float delta) {
	std::unordered_set<Physics*> remaining{Physics::members[this->level]};
	int calculations = 0;

	// TODO: Run functions with thread pool
	while(remaining.size() > 0 && calculations++ < Physics::maxIter) {
		for(Physics *member : remaining)
			member->physicsSetup(delta);

		// TODO: Require some ability to synchronize to use thread pool
		for(Physics *member : remaining)
			if(member->physicsCalculate(delta))
				remaining.erase(member);
	};
};


Physics::Physics(class Level *level) : level(level) {
	Physics::members[level].insert(this);
};

Physics::~Physics() {
	Physics::members[this->level].erase(this);
};
