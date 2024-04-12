#include "components/movement.hpp"

#include "level.hpp"
#include "input.hpp"
#include "vector.hpp"
#include "entity.hpp"

#include "components/rigidbody.hpp"

#include "log.hpp"

#include "engine.hpp"

using namespace Engine; // For Engine::input

MovementComponent::MovementComponent(Entity *entity, float speed, RigidbodyComponent *rigidbody) : Component(entity), Update(&Engine::level), speed(speed), rigidbody(rigidbody) {
	//Get the state of these keys so they are tracked
	input.pressed(SDL_SCANCODE_W);
	input.pressed(SDL_SCANCODE_A);
	input.pressed(SDL_SCANCODE_S);
	input.pressed(SDL_SCANCODE_D);
};

MovementComponent::~MovementComponent() {};


void MovementComponent::update(float delta) {
	if(!this->entity || !this->rigidbody) return;

	Engine::log.log("Updating MovementComponent", LogLevel::Debug, "MovementComponent");

	Vector2D move;

	if(input.pressed(SDL_SCANCODE_W))
		move += Vector2D(0, 1);

	if(input.pressed(SDL_SCANCODE_A))
		move += Vector2D(-1, 0);

	if(input.pressed(SDL_SCANCODE_S))
		move += Vector2D(0, -1);

	if(input.pressed(SDL_SCANCODE_D))
		move += Vector2D(1, 0);

	this->rigidbody->move(this->entity->position + move * this->speed * delta);
};

