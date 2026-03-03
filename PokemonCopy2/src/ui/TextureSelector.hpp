#ifndef TEXTURESELECTOR_HPP
#define TEXTURESELECTOR_HPP

#include "raylib.h"
#include "src/components/Sprite.hpp"
#include "src/ui/Button.hpp"

class TextureSelector
{
private:
    Rectangle bounds;
    Texture2D texture;
    Rectangle sheetRect;

    float gridSize;
    bool active;
    bool hidden;
    Rectangle selectorRect;
    Vector2 mousePosGrid;
    Rectangle textureRect;
    Font& font;

public:
    void InitButtons();
    TextureSelector(Vector2 position, 
        Vector2 size, float gridSize, 
        const Texture2D* textureSheet, Font& font);
    ~TextureSelector();

    void Update(const Vector2& mouseWindowPosition);
    void Draw();

    const Rectangle& GetSelectedRect() const;
    const bool& IsActive() const { return active; }
    const bool& IsHidden() const { return hidden; }
    void SetHidden(bool hidden) { this->hidden = hidden; }
};

#endif