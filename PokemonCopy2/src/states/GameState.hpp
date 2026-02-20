#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "src/states/State.hpp"

struct Tile
{
    int id;
    bool solid;
    int height;
    bool interactable;
};

class GameState : public State
{
private:

    Player* player;

protected:
    

public:
    GameState(std::stack<State*>* states);
    virtual ~GameState();

    void InitTextures();
    void InitPlayer();
    void Update(float deltaTime) override;
    void Draw() override;
    
    void UpdateInputs(float deltaTime) override;
};

#endif