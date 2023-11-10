#include "component.hpp"

#include "entity.hpp"

int Engine::GCID = 0;

ComponentBase::ComponentBase(Entity *entity) : entity(entity) {};
