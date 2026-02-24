#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "src/states/State.hpp"
#include "src/managers/InputManager.hpp"
#include "src/ui/PauseMenu.hpp"


class GameState : public State
{
private:

    Player* player;
    InputManager inputManager;
    PauseMenu* pauseMenu;
    Font font;
    bool isPaused;

protected:
    

public:
    GameState(std::stack<State*>* states);
    virtual ~GameState();

    void InitTextures();
    void InitPlayer();
    void InitFonts();
    void InitPauseMenu();
    void Update(float deltaTime) override;
    void Draw() override;
    
    void UpdateInputs(float deltaTime) override;
    void UpdateGameplayInputs(float deltaTime);
    void UpdateUIInputs(float deltaTime);
    void OpenPauseMenu();
    void ClosePauseMenu();
};

#endif