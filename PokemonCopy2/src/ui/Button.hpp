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
    Texture2D baseTexture;
    Texture2D hoverTexture;
    Color idleColor;
    Color hoverColor;
    Color activeColor;
    Font font;
    std::string text;
    int fontSize;
    bool active;

public:

    Button(Rectangle rect, const std::string& text, 
        Font* font, Texture2D baseTexture, Texture2D hoverTexture, 
        int fontSize = 20, Color idleColor = WHITE, 
        Color hoverColor = GRAY, Color activeColor = DARKGRAY,
        bool active = true);
    ~Button();
    
    void InitTextures();
    void SetActive(bool active) { this->active = active; }
    void Draw();
    void Update();
    void SetButtonState(ButtonState newState) { state = newState; }
    bool IsHovered() const { return state == HOVER; };
    const bool IsPressed() const { return state == PRESSED; }
    const Rectangle& GetRect() const { return rect; }

    Event<> onClick;
};

#endif