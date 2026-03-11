#ifndef BATTLEUI_HPP
#define BATTLEUI_HPP

#include "BattleDialogueBox.hpp"
#include "BattleHud.hpp"

class Battle;
enum class BattleFlowState;
enum class PlayerAction;

class BattleUI
{
public:
    BattleDialogueBox* dialogueBox;
    BattleHud playerHud;
    BattleHud enemyHud;
    BattleFlowState currentBattleState;
    PlayerAction currentPlayerAction;
    BattleUnit& playerUnit;
    BattleUnit& enemyUnit;

    Font font;
    Rectangle playerHudRect;
    Rectangle enemyHudRect;
    Rectangle textBox;
    Rectangle attackSelectionBox;

    Texture2D playerHudTexture;
    Texture2D enemyHudTexture;
    Texture2D buttonBaseTexture;
    Texture2D buttonHoverTexture;
    Texture2D textBoxTexture;
    Texture2D attackSelectionBoxTexture;

    BattleUI(Battle& battle, Font font, 
        BattleUnit& playerUnit, BattleUnit& enemyUnit);
    ~BattleUI();

    void Update();
    void Draw(BattleFlowState currentBattleState);
    void StartDraw();
    void PlayerActionDraw();
    void PlayerTurnDraw();
    void UpdateHealths();
};

#endif