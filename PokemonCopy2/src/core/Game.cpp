#include "src/core/Game.hpp"
#include "src/managers/CanvasManager.hpp"
#include "src/managers/AudioManager.hpp"

#include <iostream>
#include <fstream>

Game::Game()
{
    InitKeys();
    InitStates();
}

Game::~Game()
{
    while (!states.empty())
    {
        states.top()->EndState();
        delete states.top();
        states.pop();
    }
}

void Game::Initialize(int width, int height, const char* title)
{
    screenWidth = width;
    screenHeight = height;

    InitWindow(screenWidth, screenHeight, title);
    SetTargetFPS(60);
    InitAudioDevice();
}

void Game::InitKeys()
{
    supportedKeys.emplace("A", KEY_A);
    supportedKeys.emplace("D", KEY_D);
    supportedKeys.emplace("W", KEY_W);
    supportedKeys.emplace("S", KEY_S);
    supportedKeys.emplace("ESCAPE", KEY_ESCAPE);
}

void Game::InitStates()
{
    states.push(new GameState());
}

void Game::Draw()
{
    if (!states.empty())
        states.top()->Draw();

}

void Game::Update()
{
    if (!states.empty())
    {
        states.top()->Update();
        if (states.top()->GetQuit())
        {
            states.top()->EndState();
            delete states.top();
            states.pop();
        }
    }
    else
        CloseWindow();
}

void Game::HandleInput()
{
    
}
