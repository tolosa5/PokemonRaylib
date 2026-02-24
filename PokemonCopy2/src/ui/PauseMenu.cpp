#include "PauseMenu.hpp"

void PauseMenu::InitPanels()
{
    panels["POKEDEX"] = new PokedexPanel();
    panels["POKEMON"] = new PokemonPanel();
}

PauseMenu::PauseMenu()
{
    menuPanel = { 900, 0, 380, 720 };
    InitPanels();
}

PauseMenu::~PauseMenu()
{
    for (auto& panel : panels)
    {
        delete panel.second;
    }
}

void PauseMenu::Update(float deltaTime)
{
    for (auto& panel : panels)
    {
        panel.second->Update();
    }
}

void PauseMenu::Draw()
{
    DrawRectangleRec(menuPanel, WHITE);
    for (auto& panel : panels)
    {
        panel.second->Draw();
    }
}