#ifndef SETTINGSPANEL_HPP
#define SETTINGSPANEL_HPP

#include "Panel.hpp"

class SettingsPanel : public Panel
{
private:
    Font& font;

    std::map<std::string, Button*> buttons;
    std::vector<Button*> buttonVector;
    ButtonGroup* buttonGroup;

    Texture2D buttonBaseTexture;
    Texture2D buttonHoverTexture;

public:

    void InitTextures();
    void InitButtons();
    SettingsPanel(Font& font);
    virtual ~SettingsPanel();

    void Update() override;
    void Draw() override;
    void AudioButtonClick();
    void VideoButtonClick();
    void ControlsButtonClick();
};

#endif