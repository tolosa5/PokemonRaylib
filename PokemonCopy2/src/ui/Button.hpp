#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "raylib.h"
#include <string>
#include "src/utils/Event.hpp"

enum ButtonState
{
    IDLE,
    HOVER,
    PRESSED
};

class Button
{
private:

    ButtonState state;

    Rectangle rect;
    Texture2D texture;
    Color idleColor;
    Color hoverColor;
    Color activeColor;
    Font font;
    std::string text;
    int fontSize;

public:

    Button(Rectangle rect, const std::string& text, 
        Font* font, int fontSize = 20, Color idleColor = WHITE, 
        Color hoverColor = GRAY, Color activeColor = DARKGRAY);
    ~Button();
    
    void Update();
    void Draw();
    void SetButtonState(ButtonState newState) { state = newState; }
    bool IsHovered() const { return state == HOVER; };
    const bool IsPressed() const { return state == PRESSED; }

    Event<> onClick;
};

#endif