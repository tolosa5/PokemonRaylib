#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "src/states/State.hpp"

class GameState : public State
{
private:
    void InitKeybinds() override;

    Entity player;

protected:
    std::map<std::string, int>* supportedKeys;

public:
    GameState(std::map<std::string, int>* supportedKeys);
    virtual ~GameState();

    void Update() override;
    void Draw() override;
    
    void UpdateInputs() override;
    void EndState() override;
    void CheckForQuit() override;
};

#endif