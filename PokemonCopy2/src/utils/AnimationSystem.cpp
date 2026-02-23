#include "AnimationSystem.hpp"
#include <iostream>

void AnimationSystem::Update(AnimationComponent& animComp, float deltaTime)
{
    if(animComp.currentAnimationKey.empty())
        return;

    Animation animation = animComp.animations.at(animComp.currentAnimationKey);
    animComp.animationTimer += deltaTime;

    if (animComp.animationTimer >= animation.frameTime)
    {
        animComp.animationTimer = 0.0f;
        animComp.currentFrame = (animComp.currentFrame + 1) % animation.frameCount;
    }
    
}

void AnimationSystem::Draw(AnimationComponent& animComp, Vector2 position, float scale)
{
    Rectangle sourceRect = animComp.GetSourceRect();
    
    Rectangle destRect = 
    {
        position.x, 
        position.y, 
        sourceRect.width * scale, 
        sourceRect.height * scale
    };
    
    DrawTexturePro(animComp.textureSheet, sourceRect, destRect, Vector2{0, 0}, 0.0f, WHITE);
}