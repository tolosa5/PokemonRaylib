#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "src/states/State.hpp"
#include "src/managers/InputManager.hpp"
#include "src/ui/PauseMenu.hpp"
#include "src/map/TileMap.hpp"


class GameState : public State
{
private:

    Player* player;
    PauseMenu* pauseMenu;
    Font font;
    bool isPaused;

    TileMap* tileMap;

protected:
    

public:
    GameState(std::stack<State*>* states, float gridSize);
    virtual ~GameState();

    void InitTextures();
    void InitPlayer();
    void InitFonts();
    void InitPauseMenu();
    void InitTileMap();
    void Update(float deltaTime) override;
    void Draw() override;
    
    void UpdateInputs(float deltaTime) override;
    void UpdateGameplayInputs(float deltaTime);
    void UpdateUIInputs(float deltaTime);
    void OpenPauseMenu();
    void ClosePauseMenu();
};

#endif