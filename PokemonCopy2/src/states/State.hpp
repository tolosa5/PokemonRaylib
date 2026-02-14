#ifndef STATE_HPP
#define STATE_HPP

#include "raylib.h"
#include <vector>
#include <stack>
#include <map>
#include <string>

#include "src/entity/Entity.hpp"

class State
{
private:

protected:
    virtual void InitKeybinds() = 0;

    std::map<std::string, int>* supportedKeys;
    std::map<std::string, int> keybinds;
    bool quit;

    std::vector<Texture2D> textures;
    
public:
    State(std::map<std::string, int>* supportedKeys);
    virtual ~State();

    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void UpdateInputs() = 0;
    virtual void EndState() = 0;
    virtual void CheckForQuit();

    const bool& GetQuit() const { return quit; }
};

#endif