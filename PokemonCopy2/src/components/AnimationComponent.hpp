#ifndef ANIMATIONCOMPONENT_HPP
#define ANIMATIONCOMPONENT_HPP

#include "raylib.h"
#include <map>
#include <string>
#include "src/components/Sprite.hpp"

class AnimationComponent
{
private:
    class Animation
    {
    public:
        Sprite& sprite;
        Texture2D& textureSheet;
        Rectangle startRect;
        Rectangle currentRect;
        Rectangle endRect;
        float animationTimer;
        float timer;
        int width;
        int height;

        Animation(Sprite& sprite, Texture2D& textureSheet, Rectangle startRect, 
            Rectangle currentRect, Rectangle endRect, float animationTimer) : 
            sprite(sprite), textureSheet(textureSheet), 
            animationTimer(animationTimer), 
            width(startRect.width), height(startRect.height)
        {
            this->width = startRect.width;
            this->height = startRect.height;
            this->startRect = startRect;
            this->currentRect = currentRect;
            this->endRect = endRect;
            this->animationTimer = animationTimer;

            this->sprite.texture = textureSheet;
            this->sprite.position = {startRect.x, startRect.y};
        }

        void Play(float deltaTime)
        {
            timer = 10.0f;
            if(timer >= animationTimer)
            {
                timer = 0.0f;
                if(currentRect.x < endRect.x)
                    currentRect.x += width;
                else
                    currentRect.x = startRect.x;
            }
        };
        
        void Pause();
        void Reset()
        {
            timer = 0.0f;
            currentRect = startRect;
        }
    };
    
    Texture2D& textureSheet;
    Sprite& sprite;
    std::map<std::string, Animation*> animations;

public:
    AnimationComponent(Sprite& sprite, Texture2D& textureSheet);
    virtual ~AnimationComponent();

    void AddAnimation(std::string key, float animationTimer, 
        Rectangle startRect, Rectangle currentRect, Rectangle endRect);

    void StartAnimation(std::string animation);
    void StopAnimation(std::string animation);
    void ResetAnimation(std::string animation);

    void Play(const std::string key);
};

#endif