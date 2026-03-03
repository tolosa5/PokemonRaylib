#include "TextureSelector.hpp"

void TextureSelector::InitButtons()
{

}

TextureSelector::TextureSelector(Vector2 position, 
    Vector2 size, float gridSize, const Texture2D* textureSheet, Font& font) 
        : font(font)
{
    this->gridSize = gridSize;
    active = false;
    hidden = false;
    bounds = { position.x, position.y, size.x, size.y };
    
    texture = *textureSheet;
    sheetRect = { bounds.x, bounds.y, static_cast<float>(texture.width), 
        static_cast<float>(texture.height) };
    
    if (sheetRect.width > bounds.width)
        sheetRect.width = bounds.width;
    
    if (sheetRect.height > bounds.height)
        sheetRect.height = bounds.height;
    
    selectorRect = { bounds.x, bounds.y, gridSize, gridSize };

    textureRect.width = static_cast<int>(gridSize);
    textureRect.height = static_cast<int>(gridSize);

    InitButtons();
}

TextureSelector::~TextureSelector()
{
    
}

void TextureSelector::Update(const Vector2& mouseWindowPosition)
{
    if (hidden)
        return;

    active = CheckCollisionPointRec(mouseWindowPosition, bounds);

    if (active)
    {
        mousePosGrid.x = static_cast<int>(
            (mouseWindowPosition.x - bounds.x) / gridSize);
        mousePosGrid.y = static_cast<int>(
            (mouseWindowPosition.y - bounds.y) / gridSize);

        selectorRect.x = bounds.x + mousePosGrid.x * gridSize;
        selectorRect.y = bounds.y + mousePosGrid.y * gridSize;
    }

    textureRect.x = static_cast<int>(selectorRect.x);
    textureRect.y = static_cast<int>(selectorRect.y);
}

void TextureSelector::Draw()
{
    if (hidden)
        return;

    DrawRectangleLinesEx(bounds, 2, WHITE);
    DrawTextureRec(texture, sheetRect, { bounds.x, bounds.y }, WHITE);

    if (active)
        DrawRectangleLinesEx(selectorRect, 2, RED);
}

const Rectangle& TextureSelector::GetSelectedRect() const
{
    return textureRect;
}