#ifndef UPDATE_BAR_ACTION_HPP
#define UPDATE_BAR_ACTION_HPP

#include "BattleAction.hpp"
#include "BattleDialogueBox.hpp"
#include "HealthBar.hpp"
#include "raylib.h"
#include <string>

class UpdateBarAction : public BattleAction
{
private :
    HealthBar* healthBar;

public:
    UpdateBarAction(HealthBar* healthBar) 
        : healthBar(healthBar) {}

    void Update() override
    {
        healthBar->Update(healthBar->targetHp);
    }

    bool Finished() override
    {
        return healthBar->currentHp == healthBar->targetHp;
    }
};

#endif