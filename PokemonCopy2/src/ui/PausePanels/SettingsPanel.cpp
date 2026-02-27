#include "SettingsPanel.hpp"

void SettingsPanel::InitTextures()
{
    buttonBaseTexture = LoadTexture("assets/graphics/sprites/ui/UnselectedButton.png");
    buttonHoverTexture = LoadTexture("assets/graphics/sprites/ui/SelectedButton.png");
}

void SettingsPanel::InitButtons()
{
    buttons["AUDIO"] = new Button({ 
        panelRect.x + 20, panelRect.y + 20, 340, 50 }, "Audio", 
        &font, buttonBaseTexture, buttonHoverTexture);
    buttons["AUDIO"]->onClick.Subscribe(
        [&]() {
            AudioButtonClick(); });

    buttons["VIDEO"] = new Button({ 
        panelRect.x + 20, panelRect.y + 90, 340, 50 }, "Video", 
        &font, buttonBaseTexture, buttonHoverTexture);
    buttons["VIDEO"]->onClick.Subscribe(
        [&]() {
            VideoButtonClick(); });

    buttons["CONTROLS"] = new Button({ 
        panelRect.x + 20, panelRect.y + 160, 340, 50 }, "Controls", 
        &font, buttonBaseTexture, buttonHoverTexture);
    buttons["CONTROLS"]->onClick.Subscribe(
        [&]() {
            ControlsButtonClick(); });

    for (auto& button : buttons)
    {
        buttonVector.push_back(button.second);
    }

    buttonGroup = new ButtonGroup(buttonVector, VERTICAL, 1, 1);
}

SettingsPanel::SettingsPanel(Font& font) : 
    Panel({ 900, 0, 380, 720 }, 
    LoadTexture("assets/graphics/ui/SettingsPanel.png")), 
    font(font)
{
    InitTextures();
    InitButtons();
}

SettingsPanel::~SettingsPanel()
{
    if (backgroundTexture.id > 0)
        UnloadTexture(backgroundTexture);
    delete buttonGroup;
    for (auto& button : buttons)
    {
        delete button.second;
    }

    UnloadTexture(buttonBaseTexture);
    UnloadTexture(buttonHoverTexture);
}

void SettingsPanel::Update()
{
    if (!active)
        return;
    
    buttonGroup->Update();
}

void SettingsPanel::Draw()
{
    if (!active)
        return;
        
    DrawTextureRec(backgroundTexture, panelRect, 
        { panelRect.x, panelRect.y }, WHITE);
    buttonGroup->Draw();
}

void SettingsPanel::AudioButtonClick()
{
    
}

void SettingsPanel::VideoButtonClick()
{
    
}

void SettingsPanel::ControlsButtonClick()
{
    
}