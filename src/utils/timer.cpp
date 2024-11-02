#include "timer.h"



// Constructeur.
Timer::Timer() {
    stop();
}

// Destructeur.
Timer::~Timer() {}



// Parmet l'activation du timer.
void Timer::start() {
    started = true;
    paused = false;
    timeStart = SDL_GetTicks();
    timePause = 0;
}

// Permet l'arrêt du timer.
void Timer::stop() {
    timeStart = 0;
    timePause = 0;
    started = false;
    paused = false;
}

// Permet de mettre la pause.
void Timer::pause() {

    // Si le timer est lancé et qu'il n'est pas en pause.
    if (started && !paused) {
        timePause = SDL_GetTicks() - timeStart;
        timeStart = 0;
        paused = true;
    }
}

// Permet de retirer la pause.
void Timer::unpause() {

    // Si le timer est lancé et que la pause est active.
    if (started && paused) {
        timeStart = SDL_GetTicks() - timePause;
        timePause = 0;
        paused = false;
    }

}



// Permet de récuperer le temps écoulé depuis le lancement du timer.
// La durée renvoyée est en millisecondes.
Uint32 Timer::getTime() const {

    // Calcule le temps écoulé.
    Uint32 time = 0;
    if (started) {
        if (paused) time = timePause;
        else time = SDL_GetTicks() - timeStart;
    }
    return time;

}

// Renvoie l'état de lancement du timer.
bool Timer::isStarted() const {
    return started;
}

// Renvoie l'état de pause du timer.
bool Timer::isPaused() const {
    return paused && started;
}
