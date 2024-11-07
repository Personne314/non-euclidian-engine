#pragma once

#include <SDL2/SDL.h>



// Class Timer : Measure durations.
class Timer {

public :

    // Constructor, destructor.
    Timer();
    ~Timer();

    // Operations on the timer.
    void start();
    void stop();
    void pause();
    void unpause();

    // Getters.
    Uint32 getTime() const;
    bool isStarted() const;
    bool isPaused() const;

private :

    // Time at the start and when paused.
    Uint32 timeStart;
    Uint32 timePause;

    // Timer status.
    bool started;
    bool paused;

};
