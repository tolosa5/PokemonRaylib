#include "AnimationComponent.hpp"

AnimationComponent::AnimationComponent(Sprite &sprite, Texture2D& textureSheet)
    : sprite(sprite), textureSheet(textureSheet)
{
    
}

AnimationComponent::~AnimationComponent()
{

}

void AnimationComponent::AddAnimation(std::string key, float animationTimer, 
    Rectangle startRect, Rectangle currentRect, Rectangle endRect)
{
    animations[key] = new Animation(sprite, textureSheet, startRect, 
        currentRect, endRect, animationTimer);
}

void AnimationComponent::StartAnimation(std::string animation)
{
    animations[animation]->Play(0.0f);
}

void AnimationComponent::StopAnimation(std::string animation)
{
    animations[animation]->Pause();
}

void AnimationComponent::ResetAnimation(std::string animation)
{
    animations[animation]->Reset();
}

void AnimationComponent::Play(const std::string key)
{
    if (animations.find(key) != animations.end())
    {
        animations[key]->Play(GetFrameTime());
    }
}