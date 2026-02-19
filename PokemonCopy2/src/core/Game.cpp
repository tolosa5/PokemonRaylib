#include "src/core/Game.hpp"
#include "src/managers/CanvasManager.hpp"
#include "src/managers/AudioManager.hpp"

#include <iostream>
#include <fstream>

Game::Game()
{
    
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
    InitializeWindow(width, height, title);
    
    InitStates();
    ImportAssets();
}

void Game::InitializeWindow(int width, int height, const char* title)
{
    screenWidth = width;
    screenHeight = height;
    InitWindow(width, height, title);
    
    MaximizeWindow();
    SetTargetFPS(60);
    InitAudioDevice();
}

void Game::ImportAssets()
{
    //assets["player"] = Sprite(LoadTexture("assets/player.png"), {100, 100});
}

void Game::InitStates()
{
    states.push(new MainMenuState(&states));
}

void Game::Draw()
{
    if (!states.empty())
        states.top()->Draw();

}

void Game::Update(float deltaTime)
{
    if (!states.empty())
    {
        states.top()->Update(deltaTime);
        if (states.top()->GetQuit())
        {
            states.top()->EndState();
            delete states.top();
            states.pop();
        }
    }
}

void Game::HandleInput()
{
    
}