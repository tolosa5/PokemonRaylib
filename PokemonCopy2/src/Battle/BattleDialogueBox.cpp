#include "BattleDialogueBox.hpp"

BattleDialogueBox::BattleDialogueBox(Rectangle textBox, Texture textBoxTexture, Font font)
    : textBox(textBox), textBoxTexture(textBoxTexture), font(font)
{

}

BattleDialogueBox::~BattleDialogueBox()
{
    UnloadTexture(textBoxTexture);
}

void BattleDialogueBox::Update()
{
    if (!active)
        return;

    
}

void BattleDialogueBox::Draw()
{
    if (!active)
        return;

    DrawTexture(textBoxTexture, textBox.x, textBox.y, WHITE);
    if (currentDialogue != "")
        DrawTextEx(font, currentDialogue.c_str(), { 50, 350 }, 20, 5, BLACK);
}

void BattleDialogueBox::SetDialogue(const std::string &dialogue)
{
    active = true;
    currentDialogue = dialogue;
}