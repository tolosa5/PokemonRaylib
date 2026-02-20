#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "raylib.h"

class Sprite 
{
protected:
    

public:
    Sprite(Vector2 position = {0, 0}, Vector2 scale = {1, 1}, 
        float rotation = 0.0f, Color tint = WHITE);
    ~Sprite();
    
    void Draw();
    void Update(float deltaTime);
    void Move(Vector2 direction);

    Texture2D texture;
    Vector2 position;
    Vector2 scale;
    float rotation;
    Color tint;
};

#endif