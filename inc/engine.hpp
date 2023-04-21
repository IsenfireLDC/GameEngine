/*
 * THIS FILE MUST BE INCLUDED AFTER ALL OTHER INCLUDES
 * Do not include in header files
 *
 * Adds Engine namespace items based on already included files
 *
 * Engine constants and globals
 */

#include "engine_types.hpp"

namespace Engine {

/*
 * events.hpp
 *
 * Global event bus
 */
#ifdef _EVENTS_HPP_
#ifndef _ENGINE_EVENTS
#define _ENGINE_EVENTS
	extern Events eventBus;
#endif
#endif

/*
 * log.hpp
 *
 * Global log
 */
#ifdef _LOG_HPP_
#ifndef _ENGINE_LOG
#define _ENGINE_LOG
	extern Log log;
#endif
#endif

/*
 * input.hpp
 *
 * Global input state
 */
#ifdef _INPUT_HPP_
#ifndef _ENGINE_INPUT
#define _ENGINE_INPUT
	extern Input input;
#endif
#endif

/*
 * threads.hpp
 *
 * Default thread pool
 */
#ifdef _THREADS_HPP_
#ifndef _ENGINE_THREADS
#define _ENGINE_THREADS
	extern ThreadPool threadPool;
#endif
#endif

/*
 * level.hpp
 *
 * Default level
 */
#ifdef _LEVEL_HPP_
#ifndef _ENGINE_LEVEL
#define _ENGINE_LEVEL
	extern Level level;
#endif
#endif

};
