#ifndef TEXTURESELECTOR_HPP
#define TEXTURESELECTOR_HPP

#include "raylib.h"
#include "src/components/Sprite.hpp"

class TextureSelector
{
private:
    Rectangle bounds;
    Texture2D texture;
    Rectangle sheetRect;

    float gridSize;
    bool active;
    Rectangle selectorRect;
    Vector2 mousePosGrid;
    Rectangle textureRect;

public:
    TextureSelector(Vector2 position, 
        Vector2 size, float gridSize, const Texture2D* textureSheet);
    ~TextureSelector();
    void Update(const Vector2& mouseWindowPosition);
    void Draw();
    
    const Rectangle& GetSelectedRect() const;
    const bool& IsActive() const { return active; }
};

#endif