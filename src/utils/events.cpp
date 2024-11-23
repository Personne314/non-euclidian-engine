#include "events.h"

#include <SDL2/SDL.h>



EventManager::EventManager() : m_closeEvent(false) {}
EventManager::~EventManager() {}

void EventManager::pollEvents() {

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT: 
			m_closeEvent = true; 
			break;
		}
	}

}


void EventManager::setMouseMode(bool relative) {
	m_relative = relative;
	SDL_SetRelativeMouseMode((SDL_bool)relative);
}


bool EventManager::isCloseRequested() const {
	return m_closeEvent;
}
