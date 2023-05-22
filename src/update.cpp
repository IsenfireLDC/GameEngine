#include "update.hpp"

#include "level.hpp"
#include "threads.hpp"

#include "engine.hpp"

Level *const UpdateControllerBase::defaultLevel = &Engine::level;
ThreadPool *const UpdateControllerBase::defaultThreadPool = &Engine::threadPool;

/*
 * Perform initialization
 */
Update::Update(Level *level) : UpdateBase(level) {};

/*
 * Perform cleanup
 */
Update::~Update() {};

