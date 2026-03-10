#ifndef BUTTONGROUP_HPP
#define BUTTONGROUP_HPP

#include "raylib.h"
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include "../utils/Event.hpp"
#include "src/managers/InputManager.hpp"
#include "Button.hpp"

enum GroupMode
{
    VERTICAL,
    HORIZONTAL,
    GRID
};

class ButtonGroup
{
private:
    GroupMode mode;
    Button* hoveredButton = nullptr;
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

    void SetActive(bool active);
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

#endif