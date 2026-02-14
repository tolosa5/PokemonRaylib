#ifndef GAME_HPP
#define GAME_HPP

#pragma once

#include <stack>
#include "src/utils/Event.hpp"
#include "src/states/State.hpp"
#include "src/states/GameState.hpp"

class Game
{
private:

    void InitKeys();
    void InitStates();
    void HandleInput();

    int screenWidth;
    int screenHeight;
    
    std::stack<State*> states;
    std::map<std::string, int> supportedKeys;

public:
    Game();
    ~Game();

    void Update();
    void Initialize(int screenWidth, int screenHeight, const char* title);
    void Draw();
};

#endif