#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "src/states/State.hpp"
#include "src/managers/InputManager.hpp"


class GameState : public State
{
private:

    Player* player;
    InputManager inputManager;

protected:
    

public:
    GameState(std::stack<State*>* states);
    virtual ~GameState();

    void InitTextures();
    void InitPlayer();
    void Update(float deltaTime) override;
    void Draw() override;
    
    void UpdateInputs(float deltaTime) override;
    void UpdateGameplayInputs(float deltaTime);
    void UpdateUIInputs(float deltaTime);
};

#endif