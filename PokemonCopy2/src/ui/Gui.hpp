#ifndef GUI_HPP
#define GUI_HPP

#include "raylib.h"
#include <string>
#include "src/utils/Event.hpp"
#include "src/managers/InputManager.hpp"

enum ButtonState
{
    IDLE,
    HOVER,
    PRESSED
};

enum GroupMode
{
    VERTICAL,
    HORIZONTAL,
    GRID
};

namespace Gui
{
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

    public:

        Button(Rectangle rect, const std::string& text, 
            Font* font, int fontSize = 20, Color idleColor = WHITE, 
            Color hoverColor = GRAY, Color activeColor = DARKGRAY);
        ~Button();
        
        void InitTextures();
        void Update();
        void Draw();
        void SetButtonState(ButtonState newState) { state = newState; }
        bool IsHovered() const { return state == HOVER; };
        const bool IsPressed() const { return state == PRESSED; }
        const Rectangle& GetRect() const { return rect; }

        Event<> onClick;
    };

    class ButtonGroup
    {
    private:
        GroupMode mode;
        Button* hoveredButton;
        InputManager inputManager;

        float leftMargin = 0;
        float rightMargin = 0;
        float topMargin = 0;
        float bottomMargin = 0;

        int rows;
        int columns;

    public:
        ButtonGroup(std::vector<Button*>& buttons,
            GroupMode mode, int rows = 0, int columns = 0);
        ~ButtonGroup() = default;

        void Update();
        void Draw();
        void GridSetup();
        void ButtonsIteration();
        void VerticalIteration();
        void HorizontalIteration();
        void GridIteration();
        void HoverButton(int index);
        Button *GetHoveredButton() const;
        GroupMode GetGroupMode() const { return mode; }

        std::vector<Button*>& buttons;
    };
}

#endif