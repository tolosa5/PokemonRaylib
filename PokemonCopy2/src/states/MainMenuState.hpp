#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include "src/states/State.hpp"
#include "src/states/GameState.hpp"
#include "src/core/Button.hpp"

class MainMenuState : public State
{
private:

    Rectangle background;
    Font font;

    std::map<std::string, Button*> buttons;

protected:
    

public:
    MainMenuState();
    virtual ~MainMenuState();

    void InitButtons();
    void Update(float deltaTime) override;
    void Draw() override;

    void DrawButtons();
    
    void OnPlayButtonClick();
    void UpdateInputs(float deltaTime) override;
    void EndState() override;
    void CheckForQuit() override;
};

#endif