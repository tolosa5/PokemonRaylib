#ifndef BUTTONGROUP_HPP
#define BUTTONGROUP_HPP

#include "raylib.h"
#include <map>
#include <string>
#include <vector>
#include "../utils/Event.hpp"
#include "Button.hpp"

enum GroupMode
{
    VERTICAL,
    HORIZONTAL,
};

class ButtonGroup
{
private:
    GroupMode mode;

public:
    ButtonGroup(std::vector<Button*>& buttons, GroupMode mode);
    ~ButtonGroup() = default;

    void Update();
    void Draw();
    void ButtonsIteration();
    Button *GetHoveredButton() const;
    GroupMode GetGroupMode() const { return mode; }

    std::vector<Button*>& buttons;
};

#endif