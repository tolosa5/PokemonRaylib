#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include "src/states/State.hpp"
#include "src/states/GameState.hpp"
#include "src/ui/Button.hpp"

class MainMenuState : public State
{
private:

    Rectangle background;
    Font font;

    std::map<std::string, Button*> buttons;

protected:
    

public:
    MainMenuState(std::stack<State*>* states);
    virtual ~MainMenuState();

    void InitButtons();
    void Update(float deltaTime) override;
    void Draw() override;

    void DrawButtons();
    
    void PlayButtonClick();
    void ExitButtonClick();

    void UpdateInputs(float deltaTime) override;
    void EndState() override;
};

#endif