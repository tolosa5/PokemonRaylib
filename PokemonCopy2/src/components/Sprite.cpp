#include "Sprite.hpp"
#include "src/components/AnimationComponent.hpp"

Sprite::Sprite(Vector2 position, Vector2 size, float rotation, Color tint)
{
    this->position = position;
    this->size = size;
    this->rotation = rotation;
    this->tint = tint;
}

Sprite::~Sprite()
{
    UnloadTexture(texture);
}

void Sprite::Draw(AnimationComponent& animComp, Vector2 position, float scale)
{
    Rectangle sourceRect = animComp.GetSourceRect();
    size = { sourceRect.width, sourceRect.height };
    
    Rectangle destRect = 
    {
        position.x, 
        position.y, 
        sourceRect.width * scale,
        sourceRect.height * scale
    };
    
    DrawTexturePro(animComp.textureSheet, sourceRect, 
        destRect, Vector2{0, 0}, 0.0f, WHITE);
}

void Sprite::Update(AnimationComponent& animComp)
{
    if(animComp.currentAnimationKey.empty())
        return;

    Animation animation = animComp.animations.at(animComp.currentAnimationKey);
    animComp.animationTimer += GetFrameTime();

    if (animComp.animationTimer >= animation.frameTime)
    {
        animComp.animationTimer = 0.0f;
        animComp.currentFrame = (animComp.currentFrame + 1) % animation.frameCount;
    }
    
}

void Sprite::Move(Vector2 targetPosition)
{
    position = targetPosition;
}