#ifndef GAME_HPP
#define GAME_HPP

#pragma once

#include <stack>
#include "src/utils/Event.hpp"
#include "src/states/State.hpp"
#include "src/states/GameState.hpp"
#include "src/states/MainMenuState.hpp"
#include "src/core/Game.hpp"
#include "src/core/Sprite.hpp"

class Game
{
private:

    void InitializeWindow(int width, int height, const char* title);
    void ImportAssets();
    void InitStates();
    void HandleInput();

    int screenWidth;
    int screenHeight;
    
    std::stack<State*> states;
    std::map<std::string, Sprite> assets;

public:
    Game();
    ~Game();

    void Draw();
    void Update(float deltaTime);
    void Initialize(int screenWidth, int screenHeight, const char* title);
};

#endif