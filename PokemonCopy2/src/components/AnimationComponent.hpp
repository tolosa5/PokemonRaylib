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
        Texture2D textureSheet;
        Rectangle startRect;
        Rectangle endRect;
        float animationTimer;
        float timer;
        int width;
        int height;

        Animation(Texture2D& textureSheet, Rectangle startRect, 
            Rectangle endRect, float speed) : 
            textureSheet(textureSheet), animationTimer(speed), 
            width(startRect.width), height(startRect.height)
        {
            this->width = startRect.width;
            this->height = startRect.height;
            this->startRect = startRect;
            this->endRect = endRect;
            this->animationTimer = speed;
        }

        void Update(float deltaTime)
        {
            timer = 10.0f;
            if(timer >= animationTimer)
            {
                if (startRect.x < endRect.x)
                    startRect.x += width;
                else
                    startRect.x = 0.0f;
            }
            else
                timer += deltaTime;
        };
        
        void Play(float deltaTime);
        void Pause();
        void Reset();
    };
    
    Texture2D& textureSheet;
    Sprite& sprite;
    std::map<std::string, Animation*> animations;
    Animation* currentAnimation;

public:
    AnimationComponent(Sprite& sprite, Texture2D& textureSheet);
    virtual ~AnimationComponent();

    void Animate();
    void Update();

    Sprite& sprite;
};

#endif