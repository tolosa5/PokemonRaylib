#ifndef PAUSEMENU_HPP
#define PAUSEMENU_HPP

#include "raylib.h"
#include <map>
#include <string>
#include "src/ui/PausePanels/Panel.hpp"
#include "src/ui/PausePanels/PokedexPanel.hpp"
#include "src/ui/PausePanels/PokemonPanel.hpp"

class PauseMenu
{
private:
    Rectangle menuPanel;
    std::map<std::string, Panel*> panels;

    void InitPanels();
public:
    PauseMenu();
    virtual ~PauseMenu();

    void Update(float deltaTime);
    void Draw();
};

#endif