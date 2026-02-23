#ifndef ANIMATION_SYSTEM_HPP
#define ANIMATION_SYSTEM_HPP

#include "../components/AnimationComponent.hpp"

class AnimationSystem
{
public:
    static void Update(AnimationComponent& animComp, float deltaTime);
    static void Draw(AnimationComponent& animComp, 
        Vector2 position, float scale = 1.0f);
};

#endif