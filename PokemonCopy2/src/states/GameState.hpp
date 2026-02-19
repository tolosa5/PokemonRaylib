#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "src/states/State.hpp"

class GameState : public State
{
private:

    Entity player;

protected:
    

public:
    GameState(std::stack<State*>* states);
    virtual ~GameState();

    void Update(float deltaTime) override;
    void Draw() override;
    
    void UpdateInputs(float deltaTime) override;
    void EndState() override;
    void CheckForQuit() override;
};

#endif