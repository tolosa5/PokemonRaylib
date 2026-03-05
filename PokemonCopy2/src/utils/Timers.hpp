#ifndef TIMERS_HPP
#define TIMERS_HPP

#include "raylib.h"

class Timer
{
private:
    float duration;
    float startTime;
    bool active;
    bool repeats;

public:
    Timer(float duration, bool repeats = false, bool startActive = false);

    void Activate();
    void Deactivate();
    void Update();
};

#endif