#include "BattleUI.hpp"
#include "Battle.hpp"

BattleUI::BattleUI(Battle &battle, Font font, BattleUnit& playerUnit, BattleUnit& enemyUnit) 
    : font(font), playerUnit(playerUnit), enemyUnit(enemyUnit)
{
    this->font = font;
    playerHudTexture = LoadTexture("assets/ui/player_hud.png");
    enemyHudTexture = LoadTexture("assets/ui/enemy_hud.png");
    buttonBaseTexture = LoadTexture("assets/ui/button_base.png");
    buttonHoverTexture = LoadTexture("assets/ui/button_hover.png");
    textBoxTexture = LoadTexture("assets/ui/text_box.png");
    attackSelectionBoxTexture = LoadTexture("assets/ui/attack_selection_box.png");

    playerHudRect = { 20, 200, (float)playerHudTexture.width, 
        (float)playerHudTexture.height };
    enemyHudRect = { 400, 20, (float)enemyHudTexture.width, 
        (float)enemyHudTexture.height };
    playerHud.SetData(playerUnit, playerHudRect);
    enemyHud.SetData(enemyUnit, enemyHudRect);

    textBox = { 20, 350, (float)textBoxTexture.width, (float)textBoxTexture.height };
    attackSelectionBox = { 400, 350, (float)attackSelectionBoxTexture.width, 
        (float)attackSelectionBoxTexture.height };
    
    dialogueBox = new BattleDialogueBox(textBox, textBoxTexture, font);
}

BattleUI::~BattleUI()
{
    UnloadTexture(playerHudTexture);
    UnloadTexture(enemyHudTexture);
    UnloadTexture(buttonBaseTexture);
    UnloadTexture(buttonHoverTexture);
    UnloadTexture(textBoxTexture);
    UnloadTexture(attackSelectionBoxTexture);
    
    delete dialogueBox;
}

void BattleUI::Update()
{
    dialogueBox->Update();
}

void BattleUI::Draw(BattleFlowState currentBattleState)
{
    dialogueBox->Draw();

    switch (currentBattleState)
    {
    case BattleFlowState::NONE:
        /* code */
        break;

    case BattleFlowState::START:
        /* code */
        break;

    case BattleFlowState::PLAYER_ACTION:
        PlayerActionDraw();
        break;

    case BattleFlowState::PLAYER_TURN:
        PlayerTurnDraw();
        break;

    case BattleFlowState::ENEMY_TURN:
        PlayerTurnDraw();
        break;

    case BattleFlowState::WON:
        playerUnit.Draw();
        break;

    case BattleFlowState::LOST:
        enemyUnit.Draw();
        break;

    default:
        break;
    }

    PlayerActionDraw();
}

void BattleUI::StartDraw()
{
    
}

void BattleUI::PlayerActionDraw()
{
    switch (currentPlayerAction)
    {
    case PlayerAction::IDLE:
        playerUnit.Draw();
        enemyUnit.Draw();
        break;
    case PlayerAction::ATTACK:
        DrawTextureRec(attackSelectionBoxTexture, attackSelectionBox, 
            {attackSelectionBox.x, attackSelectionBox.y}, WHITE);
        playerUnit.Draw();
        enemyUnit.Draw();
        break;
    case PlayerAction::BAG:
        
        break;
    case PlayerAction::POKEMON:
        
        break;
    case PlayerAction::TURN:
        
        break;
    default:
        break;
    }
}

void BattleUI::PlayerTurnDraw()
{
    playerUnit.Draw();
    enemyUnit.Draw();
}