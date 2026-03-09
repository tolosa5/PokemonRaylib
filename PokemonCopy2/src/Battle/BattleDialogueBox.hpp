#ifndef BATTLEDIALOGUEBOX_HPP
#define BATTLEDIALOGUEBOX_HPP

#include <string>
#include "raylib.h"

class BattleDialogueBox
{
public:
    BattleDialogueBox();
    ~BattleDialogueBox();

    void Update();
    void Draw();

    void SetDialogue(const std::string& dialogue);
};

#endif