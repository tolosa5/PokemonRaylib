#include "SettingsPanel.hpp"

void SettingsPanel::InitButtons()
{
    buttons["AUDIO"] = new Button({ 
        panelRect.x + 20, panelRect.y + 20, 340, 50 }, "Audio", &font);
    buttons["AUDIO"]->onClick.Subscribe(
        [&]() {
            AudioButtonClick(); });

    buttons["VIDEO"] = new Button({ 
        panelRect.x + 20, panelRect.y + 90, 340, 50 }, "Video", &font);
    buttons["VIDEO"]->onClick.Subscribe(
        [&]() {
            VideoButtonClick(); });

    buttons["CONTROLS"] = new Button({ 
        panelRect.x + 20, panelRect.y + 160, 340, 50 }, "Controls", &font);
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
    InitButtons();
}

SettingsPanel::~SettingsPanel()
{
    UnloadTexture(backgroundTexture);
    delete buttonGroup;
    for (auto& button : buttons)
    {
        delete button.second;
    }
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