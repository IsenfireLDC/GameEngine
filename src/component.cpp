#include "component.hpp"

std::vector<std::unordered_set<ComponentBase*>> Engine::components;

int Engine::GCID = 0;
