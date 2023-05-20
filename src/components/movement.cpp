#include "components/movement.hpp"

//TODO: Create something usable
//Currently, this is a dump spot for code removed from Entity


/*
 * Moves entity, checking for collision if registered to manager
 */
bool Entity::move(Coord pos) {
	Engine::log.log("Attempting to move entity");

	//Check if entity at pos
	Entity* other = nullptr;
	if(this->manager) {
		if(!this->manager->inBounds(pos)) return false;
		other = this->manager->getEntityAt(pos);
	};

	//Interact with entity
	bool move = this->moveInto(other);

	//Move entity
	if(move) {
		Engine::log.log("Moving entity");
		this->pos = pos;
	};

	this->dirty = move;

	return move;
};



/*
 * Controls interaction from moving into other entities
 */
bool Entity::moveInto(Entity *other) {
	this->dirty = true;
	if(!other) return true;

	return false;
};
