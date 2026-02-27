#include "PauseMenu.hpp"

void PauseMenu::InitPanels()
{
    /*
    panels["POKEDEX"] = new PokedexPanel();
    panels["POKEMON"] = new PokemonPanel();
    panels["BAG"] = new Panel();
    panels["CARNET"] = new Panel();
    panels["SAVE"] = new Panel();
    panels["SETTINGS"] = new SettingsPanel(font);
    */
}

void PauseMenu::InitTextures()
{
    backgroundTexture = LoadTexture("assets/graphics/ui/PauseMenu.png");
    buttonBaseTexture = LoadTexture("assets/graphics/sprites/ui/UnselectedButton.png");
    buttonHoverTexture = LoadTexture("assets/graphics/sprites/ui/SelectedButton.png");
}

void PauseMenu::InitButtons()
{
    buttons["POKEDEX"] = new Button({ 900, 0, 100, 100 }, "Pokedex", 
        &font, buttonBaseTexture, buttonHoverTexture);
    buttons["POKEDEX"]->onClick.Subscribe(
        [&]() {
            PokedexButtonClick(); });

    buttons["POKEMON"] = new Button({ 900, 50, 100, 100 }, "Pokemon", 
        &font, buttonBaseTexture, buttonHoverTexture);
    buttons["POKEMON"]->onClick.Subscribe(
        [&]() {
            PokemonButtonClick(); });

    buttons["BAG"] = new Button({ 900, 100, 100, 100 }, "Bag", 
        &font, buttonBaseTexture, buttonHoverTexture);
    buttons["BAG"]->onClick.Subscribe(
        [&]() {
            BagButtonClick(); });

    buttons["CARNET"] = new Button({ 900, 150, 100, 100 }, "Carnet", 
        &font, buttonBaseTexture, buttonHoverTexture);
    buttons["CARNET"]->onClick.Subscribe(
        [&]() {
            CarnetButtonClick(); });

    buttons["SAVE"] = new Button({ 900, 200, 100, 100 }, "Save", 
        &font, buttonBaseTexture, buttonHoverTexture);
    buttons["SAVE"]->onClick.Subscribe(
        [&]() {
            SaveButtonClick(); });

    buttons["SETTINGS"] = new Button({ 900, 250, 380, 50 }, "Settings", 
        &font, buttonBaseTexture, buttonHoverTexture);
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
    InitTextures();
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

    delete buttonGroup;

    if (backgroundTexture.id > 0)
        UnloadTexture(backgroundTexture);
    if (buttonBaseTexture.id > 0)
        UnloadTexture(buttonBaseTexture);
    if (buttonHoverTexture.id > 0)
        UnloadTexture(buttonHoverTexture);
}

void PauseMenu::Update()
{
    if (AnyPanelActive())
        return;
    
    for (auto& panel : panels)
    {
        panel.second->Update();
    }
}

void PauseMenu::UpdateInputs()
{
    if (AnyPanelActive())
        return;

    buttonGroup->Update();
}

void PauseMenu::Draw()
{
    if (AnyPanelActive())
        return;

    DrawTextureRec(backgroundTexture, menuPanel, 
        { menuPanel.x, menuPanel.y }, WHITE);

    for (auto& panel : panels)
    {
        panel.second->Draw();
    }
    buttonGroup->Draw();
}

#pragma region Button Clicks

void PauseMenu::PokedexButtonClick()
{
    panels["POKEDEX"]->SetActive(true);
}

void PauseMenu::PokemonButtonClick()
{
    panels["POKEMON"]->SetActive(true);
}

void PauseMenu::BagButtonClick()
{
    panels["BAG"]->SetActive(true);
}

void PauseMenu::CarnetButtonClick()
{
    panels["CARNET"]->SetActive(true);
}

void PauseMenu::SaveButtonClick()
{
    panels["SAVE"]->SetActive(true);
}

void PauseMenu::SettingsButtonClick()
{
    panels["SETTINGS"]->SetActive(true);
}

#pragma endregion

bool PauseMenu::AnyPanelActive()
{
    for (auto& panel : panels)
    {
        if (panel.second->IsActive())
        {
            return true;
        }
    }
    return false;
}