#pragma once

#include <SDL2/SDL.h>



// Class Timer : Compte des durées.
class Timer {

public :

    // Constructeur, destructeur.
    Timer();
    ~Timer();

    // Manipulateurs du timer.
    void start();
    void stop();
    void pause();
    void unpause();

    // Getters.
    Uint32 getTime() const;
    bool isStarted() const;
    bool isPaused() const;

private :

    // Variables de temps.
    Uint32 timeStart;
    Uint32 timePause;

    // Etat du timer.
    bool started;
    bool paused;

};
