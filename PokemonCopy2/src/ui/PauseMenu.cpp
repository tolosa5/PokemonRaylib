#include "PauseMenu.hpp"

void PauseMenu::InitPanels()
{
    /*
    panels["POKEDEX"] = new PokedexPanel();
    panels["POKEMON"] = new PokemonPanel();
    panels["BAG"] = new Panel();
    panels["CARNET"] = new Panel();
    panels["SAVE"] = new Panel();
    panels["SETTINGS"] = new Panel();
    */
}

void PauseMenu::InitButtons()
{
    buttons["POKEDEX"] = new Button({ 900, 0, 380, 50 }, "Pokedex", &font);
    buttons["POKEDEX"]->onClick.Subscribe(
        [&]() {
            PokedexButtonClick(); });

    buttons["POKEMON"] = new Button({ 900, 50, 380, 50 }, "Pokemon", &font);
    buttons["POKEMON"]->onClick.Subscribe(
        [&]() {
            PokemonButtonClick(); });

    buttons["BAG"] = new Button({ 900, 100, 380, 50 }, "Bag", &font);
    buttons["BAG"]->onClick.Subscribe(
        [&]() {
            BagButtonClick(); });

    buttons["CARNET"] = new Button({ 900, 150, 380, 50 }, "Carnet", &font);
    buttons["CARNET"]->onClick.Subscribe(
        [&]() {
            CarnetButtonClick(); });

    buttons["SAVE"] = new Button({ 900, 200, 380, 50 }, "Save", &font);
    buttons["SAVE"]->onClick.Subscribe(
        [&]() {
            SaveButtonClick(); });

    buttons["SETTINGS"] = new Button({ 900, 250, 380, 50 }, "Settings", &font);
    buttons["SETTINGS"]->onClick.Subscribe(
        [&]() {
            SettingsButtonClick(); });

    for (const auto& button : buttons)
    {
        buttonVector.push_back(button.second);
    }
    buttonGroup = new ButtonGroup(buttonVector, VERTICAL);
}

PauseMenu::PauseMenu(Font& font) 
    : font(font)
{
    menuPanel = { 900, 0, 380, 720 };
    InitPanels();
    InitButtons();
}

PauseMenu::~PauseMenu()
{
    for (auto& panel : panels)
    {
        delete panel.second;
    }
    for (auto& button : buttons)
    {
        delete button.second;
    }
}

void PauseMenu::Update()
{
    for (auto& panel : panels)
    {
        panel.second->Update();
    }
}

void PauseMenu::UpdateInputs()
{
    buttonGroup->Update();
}

void PauseMenu::Draw()
{
    DrawTextureRec(backgroundTexture, menuPanel, { menuPanel.x, menuPanel.y }, WHITE);
    for (auto& panel : panels)
    {
        panel.second->Draw();
    }
    buttonGroup->Draw();
}

#pragma region Button Clicks

void PauseMenu::PokedexButtonClick()
{

}

void PauseMenu::PokemonButtonClick()
{

}

void PauseMenu::BagButtonClick()
{

}

void PauseMenu::CarnetButtonClick()
{

}

void PauseMenu::SaveButtonClick()
{

}

void PauseMenu::SettingsButtonClick()
{

}

#pragma endregion