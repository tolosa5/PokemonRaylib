#include "Button.hpp"

Button::Button(Rectangle rect, const std::string& text, 
    Font* font, int fontSize, Color idleColor, Color hoverColor, Color activeColor)
{
    this->rect = rect;
    this->state = IDLE;

    this->text = text;
    this->font = *font;
    this->fontSize = fontSize;
    
    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;
}

Button::~Button()
{

}

void Button::Draw()
{
    Color currentColor = idleColor;
    switch (state)
    {
        case IDLE:
        {
            currentColor = idleColor;
            break;
        }
        case HOVER:
        {
            currentColor = hoverColor;
            break;
        }
        case PRESSED:
        {
            currentColor = activeColor;
            break;
        }

        default:
            break;
    }
    
    DrawRectangleRec(rect, currentColor);

    int textWidth = MeasureText(text.c_str(), fontSize);
    int textX = rect.x + (rect.width - textWidth) / 2;
    int textY = rect.y + (rect.height - fontSize) / 2;
    DrawTextEx(font, text.c_str(), (Vector2){textX, textY}, fontSize, 0, BLACK);
}

void Button::Update(Vector2 mousePos)
{
    state = IDLE;
    if (CheckCollisionPointRec(mousePos, rect))
    {
        state = HOVER;
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            state = PRESSED;
            onClick.Invoke();
        }
    }
}

bool Button::IsHovered() const
{
    return state == HOVER;
}