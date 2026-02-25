#ifndef PANEL_HPP
#define PANEL_HPP

#include "raylib.h"
#include "src/ui/ButtonGroup.hpp"

class Panel
{
protected:
    Rectangle panelRect;
    Texture2D backgroundTexture;
    bool active;

    std::map<std::string, Button*> buttons;
    std::vector<Button*> panelButtonsVector;

public:
    Panel(Rectangle panelRect, Texture2D backgroundTexture)
        : panelRect(panelRect), backgroundTexture(backgroundTexture), 
        active(false) {};
    virtual ~Panel() = default;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    void ExitPanel();
    bool IsActive() const { return active; }
    void SetActive(bool isActive) { active = isActive; }
};

#endif