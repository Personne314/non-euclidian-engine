#include "events.h"

#include <SDL2/SDL.h>



EventManager::EventManager() : closeEvent(false) {}
EventManager::~EventManager() {}

void EventManager::pollEvents() {

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT: 
			closeEvent = true; 
			break;
		}
	}

}

bool EventManager::isCloseRequested() const {
	return closeEvent;
}
