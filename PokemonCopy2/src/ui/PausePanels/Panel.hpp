#ifndef PANEL_HPP
#define PANEL_HPP

#include "raylib.h"
#include "src/ui/ButtonGroup.hpp"

class Panel
{
private:
    Rectangle panelRect;
    std::vector<Button*> panelButtons;

public:
    ButtonGroup buttonGroup{ panelButtons, VERTICAL, 1, 1 };

    Panel() : panelRect{0, 0, 0, 0} {}
    virtual ~Panel() = default;
    virtual void Update() = 0;
    virtual void Draw() = 0;
};

#endif