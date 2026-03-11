#ifndef HEALTH_BAR_HPP
#define HEALTH_BAR_HPP

#include "raylib.h"
#include "src/utils/Utils.hpp"

class HealthBar
{
public:
    Rectangle barRect;
    float currentHp;
    float targetHp;

    HealthBar(Rectangle barRect, float maxHealth);
    void Update(float newHealth);
    void Draw();
};

#endif