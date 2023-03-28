#include "update.hpp"

#include "threads.hpp"

#include "engine.hpp"

// Hold all active updateable objects
std::unordered_set<Update*> Update::members;

/*
 * Register this object to the update set
 */
Update::Update() {
	Update::members.insert(this);
};

/*
 * Unregister this object from the update set
 */
Update::~Update() {
	Update::members.erase(this);
};



/*
 * Update all registered objects
 *
 * Uses engine thread pool to run
 */
void Update::updateAll(float delta) {
	for(Update *update : Update::members) {
		if(update->doUpdate)
			Engine::threadPool.add(std::bind(update->update, update, delta));
	};
};
