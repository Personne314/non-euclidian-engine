#include "timer.h"



// Constructor.
Timer::Timer() {
	stop();
}

// Destructor.
Timer::~Timer() {}


// Starts the timer.
void Timer::start() {
	started = true;
	paused = false;
	timeStart = SDL_GetTicks();
	timePause = 0;
}

// Stops and reset the timer.
void Timer::stop() {
	timeStart = 0;
	timePause = 0;
	started = false;
	paused = false;
}

// Pauses the timer.
void Timer::pause() {
	if (started && !paused) {
		timePause = SDL_GetTicks() - timeStart;
		timeStart = 0;
		paused = true;
	}
}

// Unpauses the timer.
void Timer::unpause() {
	if (started && paused) {
		timeStart = SDL_GetTicks() - timePause;
		timePause = 0;
		paused = false;
	}
}


// Retrieves the elapsed time since the timer started.
// The returned duration is in milliseconds.
Uint32 Timer::getTime() const {

	// Calcule le temps écoulé.
	Uint32 time = 0;
	if (started) {
		if (paused) time = timePause;
		else time = SDL_GetTicks() - timeStart;
	}
	return time;

}

// Returns the start status of the timer.
bool Timer::isStarted() const {
	return started;
}

// Renvoie l'état de pause du timer.
bool Timer::isPaused() const {
	return paused && started;
}
