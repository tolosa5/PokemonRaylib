#ifndef GAME_HPP
#define GAME_HPP

#pragma once

#include <stack>
#include "src/utils/Event.hpp"
#include "src/states/State.hpp"
#include "src/states/GameState.hpp"
#include "src/states/MainMenuState.hpp"

class Game
{
private:

    void InitStates();
    void HandleInput();

    int screenWidth;
    int screenHeight;
    
    std::stack<State*> states;

public:
    Game();
    ~Game();

    void Update(float deltaTime);
    void Initialize(int screenWidth, int screenHeight, const char* title);
    void Draw();
};

#endif