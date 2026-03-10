#ifndef BATTLEDIALOGUEBOX_HPP
#define BATTLEDIALOGUEBOX_HPP

#include <string>
#include "raylib.h"

class BattleDialogueBox
{
private:
    Texture textBoxTexture;
    Rectangle textBox;
    Font font;
    bool active;
    std::string currentDialogue;

public:
    BattleDialogueBox(Rectangle textBox, Texture textBoxTexture, Font font);
    ~BattleDialogueBox();

    void SetActive(bool active) { this->active = active; }
    void Update();
    void Draw();

    void SetDialogue(const std::string& dialogue);
};

#endif