#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include "src/states/State.hpp"
#include "src/states/GameState.hpp"
#include "src/ui/Button.hpp"

class ButtonGroup;

class MainMenuState : public State
{
private:

    Texture2D backgroundTexture;
    Font font;

    std::map<std::string, Button*> buttons;
    ButtonGroup* buttonGroup;
    std::vector<Button*> buttonVector;

protected:
    

public:
    MainMenuState(std::stack<State*>* states);
    virtual ~MainMenuState();

    void InitBackground();
    void InitButtons();
    void Update(float deltaTime) override;
    void Draw() override;

    void DrawButtons();
    
    void PlayButtonClick();
    void ExitButtonClick();

    void UpdateInputs(float deltaTime) override;
};

#endif