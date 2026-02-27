#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include "src/states/State.hpp"
#include "src/states/GameState.hpp"
#include "src/states/EditorState.hpp"
#include "src/ui/Button.hpp"
#include "src/managers/InputManager.hpp"

class ButtonGroup;

class MainMenuState : public State
{
private:

    Rectangle bgRect;
    Font font;
    bool customFontLoaded = false;

    std::map<std::string, Button*> buttons;
    ButtonGroup* buttonGroup;
    std::vector<Button*> buttonVector;
    Texture2D playButtonBaseTexture;
    Texture2D playButtonHoverTexture;
    
    Texture2D settingsButtonBaseTexture;
    Texture2D settingsButtonHoverTexture;

protected:
    

public:
    MainMenuState(std::stack<State*>* states, float gridSize);
    virtual ~MainMenuState();

    void InitTextures();
    void InitBackground();
    void InitButtons();
    void Update(float deltaTime) override;
    void Draw() override;

    void DrawButtons();
    
    void PlayButtonClick();
    void ExitButtonClick();
    void EditorButtonClick();

    void UpdateInputs(float deltaTime) override;
};

#endif