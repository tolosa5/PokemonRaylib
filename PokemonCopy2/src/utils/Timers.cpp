#include "Timers.hpp"

Timer::Timer(float duration, bool repeats, bool startActive)
{
    this->duration = duration;
    this->repeats = repeats;
    this->active = false;
    completed = false;

    if (startActive)
        Activate();
}

void Timer::Activate()
{
    active = true;
    startTime = GetTime();
}

void Timer::Deactivate()
{
    active = false;
    startTime = 0;
    completed = false;
    if (repeats)
        Activate();
}

void Timer::Update()
{
    if (!active)
        return;
    
    if (GetTime() - startTime >= duration)
    {
        completed = true;
        Deactivate();
    }
}