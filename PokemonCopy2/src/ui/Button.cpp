#include "Button.hpp"

Button::Button(Rectangle rect, const std::string& text, 
    Font* font, int fontSize, Color idleColor, 
    Color hoverColor, Color activeColor)
{
    this->rect = rect;
    this->state = IDLE;

    this->text = text;
    this->font = *font;
    this->fontSize = fontSize;
    
    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;

    InitTextures();
}

void Button::InitTextures()
{
    baseTexture = LoadTexture("assets/graphics/sprites/ui/UnselectedButton.png");
    hoverTexture = LoadTexture("assets/graphics/sprites/ui/SelectedButton.png");
}

Button::~Button()
{
    UnloadTexture(baseTexture);
    UnloadTexture(hoverTexture);
}

void Button::Draw()
{
    Color currentColor = idleColor;
    switch (state)
    {
        case IDLE:
        {
            DrawTexture(baseTexture, rect.x, rect.y, WHITE);
            break;
        }
        case HOVER:
        {
            DrawTexture(hoverTexture, rect.x, rect.y, WHITE);
            break;
        }
        case PRESSED:
        {
            DrawTexture(hoverTexture, rect.x, rect.y, WHITE);
            break;
        }

        default:
            break;
    }

    int textWidth = MeasureText(text.c_str(), fontSize);
    int textX = rect.x;
    int textY = rect.y;
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