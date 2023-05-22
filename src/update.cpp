#include "update.hpp"

#include "level.hpp"
#include "threads.hpp"

#include "engine.hpp"

Level *UpdateControllerBase::defaultLevel = &Engine::level;
ThreadPool *UpdateControllerBase::defaultThreadPool = &Engine::threadPool;

/*
 * Perform initialization
 */
Update::Update() {};

/*
 * Perform cleanup
 */
Update::~Update() {};

