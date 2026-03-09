#ifndef BATTLEUI_HPP
#define BATTLEUI_HPP

#include "Battle.hpp"
#include "BattleDialogueBox.hpp"

class BattleUI
{
public:
    Font font;

    BattleUI(Battle& battle, Font font);
    ~BattleUI();

    void Update();
    void Draw();

    BattleDialogueBox dialogueBox;
};

#endif