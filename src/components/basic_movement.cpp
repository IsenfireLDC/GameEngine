#include "components/basic_movement.hpp"

#include "level.hpp"
#include "input.hpp"
#include "pos.hpp"

#include "log.hpp"

#include "engine.hpp"

using namespace Engine; // For Engine::input

BasicMovementComponent::BasicMovementComponent(float speed) : Update(&Engine::level), speed(speed) {
	//Get the state of these keys so they are tracked
	input.pressed(SDL_SCANCODE_W);
	input.pressed(SDL_SCANCODE_A);
	input.pressed(SDL_SCANCODE_S);
	input.pressed(SDL_SCANCODE_D);
};

BasicMovementComponent::~BasicMovementComponent() {};


void BasicMovementComponent::update(float delta) {
	if(!this->entity) return;

	Engine::log.log("Updating BasicMovementComponent", LogLevel::Debug, "BasicMovementComponent");

	Coord move;

	if(input.pressed(SDL_SCANCODE_W))
		move += Coord(0, 1);

	if(input.pressed(SDL_SCANCODE_A))
		move += Coord(-1, 0);

	if(input.pressed(SDL_SCANCODE_S))
		move += Coord(0, -1);

	if(input.pressed(SDL_SCANCODE_D))
		move += Coord(1, 0);

	this->entity->pos += move * this->speed * delta;
};



/************************* CODE FROM ENTITY *************************/

/*
 * Moves entity, checking for collision if registered to manager
 */
//bool Entity::move(Coord pos) {
//	Engine::log.log("Attempting to move entity");
//
//	//Check if entity at pos
//	Entity* other = nullptr;
//	if(this->manager) {
//		if(!this->manager->inBounds(pos)) return false;
//		other = this->manager->getEntityAt(pos);
//	};
//
//	//Interact with entity
//	bool move = this->moveInto(other);
//
//	//Move entity
//	if(move) {
//		Engine::log.log("Moving entity");
//		this->pos = pos;
//	};
//
//	this->dirty = move;
//
//	return move;
//};
//
//
//
///*
// * Controls interaction from moving into other entities
// */
//bool Entity::moveInto(Entity *other) {
//	this->dirty = true;
//	if(!other) return true;
//
//	return false;
//};
