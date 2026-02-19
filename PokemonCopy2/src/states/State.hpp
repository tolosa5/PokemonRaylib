#ifndef STATE_HPP
#define STATE_HPP

#include "raylib.h"
#include <vector>
#include <stack>
#include <map>
#include <string>

#include "src/utils/Event.hpp"
#include "src/entity/Entity.hpp"

class State
{
private:

protected:
    bool quit;
    std::vector<Texture2D> textures;
    Vector2 mousePosScreen;
    Vector2 mousePosWindow;
    Vector2 mousePosView;

    std::stack<State*>* states;
    
public:
    State(std::stack<State*>* states);
    virtual ~State();

    virtual void Update(float deltaTime) = 0;
    virtual void Draw() = 0;
    virtual void UpdateInputs(float deltaTime) = 0;
    virtual void EndState() = 0;
    virtual void CheckForQuit();

    const bool& GetQuit() const { return quit; }
};

#endif