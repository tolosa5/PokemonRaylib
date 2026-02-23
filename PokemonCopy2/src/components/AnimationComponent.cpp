#include "AnimationComponent.hpp"

AnimationComponent::AnimationComponent(Texture2D& textureSheet, 
    int frameWidth, int frameHeight)
    : textureSheet(textureSheet), 
    frameWidth(frameWidth), frameHeight(frameHeight)
{
    
}

AnimationComponent::~AnimationComponent()
{

}

void AnimationComponent::AddAnimation(const std::string key, int row, 
    int frameCount, float frameTime)
{
    animations[key] = {frameCount, frameTime, row};
}

void AnimationComponent::ChangeSpriteSheet(Texture2D& newTexture)
{
    textureSheet = newTexture;
}

void AnimationComponent::Play(const std::string key)
{
    if (currentAnimationKey == key)
        return;

    currentAnimationKey = key;
    currentFrame = 0;
    animationTimer = 0.0f;
}

void AnimationComponent::StopAnimation(std::string animation)
{
    if (currentAnimationKey == animation)
    {
        currentAnimationKey = "";
        currentFrame = 0;
        animationTimer = 0.0f;
    }
}

void AnimationComponent::ResetAnimation(std::string animation)
{
    if (currentAnimationKey == animation)
    {
        currentFrame = 0;
        animationTimer = 0.0f;
    }
}

Rectangle AnimationComponent::GetSourceRect() const
{
    if (currentAnimationKey.empty())
        return {0, 0, (float)frameWidth, (float)frameHeight};

    const Animation& anim = animations.at(currentAnimationKey);
    return {(float)(currentFrame * frameWidth), 
        (float)(anim.row * frameHeight), 
        (float)frameWidth, 
        (float)frameHeight};
}