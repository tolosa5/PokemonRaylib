#ifndef STATE_HPP
#define STATE_HPP

#include "raylib.h"
#include <vector>
#include <stack>
#include <map>
#include <string>

#include "src/utils/Event.hpp"
#include "src/entity/Player.hpp"
#include "src/utils/Utils.hpp"

class State
{
private:

protected:
    bool quit;
    std::map<std::string, Texture2D> textures;

    std::stack<State*>* states;
    float gridSize;
    Vector2 mousePosGrid;
    
public:
    State(std::stack<State*>* states, float gridSize);
    virtual ~State();

    virtual void Update(float deltaTime);
    virtual void Draw() = 0;
    virtual void UpdateInputs(float deltaTime) = 0;
    void UpdateMousePositions();
    virtual void EndState();

    const bool& GetQuit() const { return quit; }
};

#endif