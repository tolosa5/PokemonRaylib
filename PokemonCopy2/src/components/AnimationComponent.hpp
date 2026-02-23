#ifndef ANIMATIONCOMPONENT_HPP
#define ANIMATIONCOMPONENT_HPP

#include "raylib.h"
#include <map>
#include <string>
#include <unordered_map>
#include "src/components/Sprite.hpp"

struct Animation
{
    int frameCount;
    float frameTime;
    int row;
};

class AnimationComponent
{
private:
    

public:
    Texture2D textureSheet;
    std::unordered_map<std::string, Animation> animations;
    std::string currentAnimationKey;
    int currentFrame;
    float animationTimer;
    int frameWidth;
    int frameHeight;


    AnimationComponent(Texture2D& textureSheet, 
        int frameWidth, int frameHeight);
    virtual ~AnimationComponent();

    void AddAnimation(const std::string key, int row, 
        int frames, float frameTime);
    void ChangeSpriteSheet(Texture2D& newTexture);
    void Play(const std::string key);
    void StopAnimation(std::string animation);
    void ResetAnimation(std::string animation);

    Rectangle GetSourceRect() const;
};

#endif