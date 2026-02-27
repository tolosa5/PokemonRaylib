#include "Button.hpp"

Button::Button(Rectangle rect, const std::string& text, 
    Font* font, Texture2D baseTexture, Texture2D hoverTexture,
    int fontSize, Color idleColor, 
    Color hoverColor, Color activeColor)
{
    this->rect = rect;
    this->state = IDLE;

    this->text = text;
    if (font && font->texture.id > 0)
        this->font = *font;
    else
        this->font = GetFontDefault();
    this->fontSize = fontSize;
    
    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;

    this->baseTexture = baseTexture;
    this->hoverTexture = hoverTexture;
}

void Button::InitTextures()
{
    baseTexture = LoadTexture("assets/graphics/sprites/ui/UnselectedButton.png");
    hoverTexture = LoadTexture("assets/graphics/sprites/ui/SelectedButton.png");
}

Button::~Button()
{
    
}

void Button::Draw()
{
    Color currentColor = idleColor;
    Texture2D currentTexture = baseTexture;
    switch (state)
    {
        case IDLE:
        {
            currentTexture = baseTexture;
            if (currentTexture.id > 0)
                DrawTexture(currentTexture, rect.x, rect.y, WHITE);
            else
                DrawRectangleRec(rect, idleColor);
            break;
        }
        case HOVER:
        {
            currentTexture = hoverTexture;
            if (currentTexture.id > 0)
                DrawTexture(currentTexture, rect.x, rect.y, WHITE);
            else
                DrawRectangleRec(rect, hoverColor);
            break;
        }
        case PRESSED:
        {
            currentTexture = hoverTexture;
            if (currentTexture.id > 0)
                DrawTexture(currentTexture, rect.x, rect.y, WHITE);
            else
                DrawRectangleRec(rect, activeColor);
            break;
        }

        default:
            break;
    }

    int textWidth = MeasureText(text.c_str(), fontSize);

    float drawWidth = (currentTexture.id > 0) ? 
    static_cast<float>(currentTexture.width) : rect.width;

    float drawHeight = (currentTexture.id > 0) ? 
    static_cast<float>(currentTexture.height) : rect.height;
    
    int textX = static_cast<int>(rect.x + drawWidth / 2 - textWidth / 2);
    int textY = static_cast<int>(rect.y + drawHeight / 2 - fontSize / 2);
    DrawTextEx(font, text.c_str(), (Vector2){textX, textY}, fontSize, 0, BLACK);
}

void Button::Update()
{
    if (state == HOVER)
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            state = PRESSED;
            onClick.Invoke();
        }
    }
}