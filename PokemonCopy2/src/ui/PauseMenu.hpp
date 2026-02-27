#ifndef PAUSEMENU_HPP
#define PAUSEMENU_HPP

#include "raylib.h"
#include <map>
#include <string>
#include "src/ui/ButtonGroup.hpp"
#include "src/ui/PausePanels/Panel.hpp"
#include "src/ui/PausePanels/PokedexPanel.hpp"
#include "src/ui/PausePanels/PokemonPanel.hpp"
//#include "src/ui/PausePanels/BagPanel.hpp"
//#include "src/ui/PausePanels/CarnetPanel.hpp"
//#include "src/ui/PausePanels/SavePanel.hpp"
#include "src/ui/PausePanels/SettingsPanel.hpp"

class PauseMenu
{
private:
    Rectangle menuPanel;
    Texture2D backgroundTexture;
    Font& font;

    std::map<std::string, Panel*> panels;
    std::map<std::string, Button*> buttons;
    std::vector<Button*> buttonVector;
    ButtonGroup* buttonGroup;

    Texture2D buttonBaseTexture;
    Texture2D buttonHoverTexture;


    void InitPanels();
    void InitButtons();
    void InitTextures();
    void PokedexButtonClick();
    void PokemonButtonClick();
    void BagButtonClick();
    void CarnetButtonClick();
    void SaveButtonClick();
    void SettingsButtonClick();
    bool AnyPanelActive();
public:
    PauseMenu(Font& font);
    virtual ~PauseMenu();

    void Update();
    void UpdateInputs();
    void Draw();
};

#endif