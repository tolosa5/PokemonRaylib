#ifndef BATTLE_TEXT_ACTION_HPP
#define BATTLE_TEXT_ACTION_HPP

#include "BattleAction.hpp"
#include "BattleDialogueBox.hpp"
#include "src/utils/Timers.hpp"
#include "raylib.h"
#include <string>

class BattleTextAction : public BattleAction
{
private :
    BattleDialogueBox* dialogueBox;
    Timer* timer;
    std::string text;
    float time;
    bool finished = false;

public:
    
    BattleTextAction(const std::string& text, 
        BattleDialogueBox* dialogueBox, float time) 
        : text(text), 
        dialogueBox(dialogueBox),
        time(time) {}

    void Start() override
    {
        dialogueBox->SetDialogue(text);
        timer = new Timer(time, false, true);
    }

    void Update() override
    {
        if (finished)
            return;
            
        if (IsKeyPressed(KEY_ENTER))
            finished = true; 

        timer->Update();
        if (timer->IsCompleted())
            finished = true;
    }

    bool Finished() override
    {
        return finished;
    }
};

#endif