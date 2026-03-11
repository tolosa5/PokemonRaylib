#ifndef WAITUNTIL_HPP
#define WAITUNTIL_HPP

#include <functional>

struct WaitUntil
{
    std::function<bool()> condition;
    bool finished = false;

    void Update()
    {
        if (condition())
            finished = true;
    }
};

#endif