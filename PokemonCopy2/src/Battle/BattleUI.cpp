#include "BattleUI.hpp"
#include "Battle.hpp"

BattleUI::BattleUI(Battle &battle, Font font, BattleUnit& playerUnit, 
    BattleUnit& enemyUnit) 
    : font(font), playerUnit(playerUnit), enemyUnit(enemyUnit)
{
    this->font = font;
    
    playerHud.hudTexture = LoadTexture("assets/ui/player_hud.png");
    enemyHud.hudTexture = LoadTexture("assets/ui/enemy_hud.png");
    buttonBaseTexture = LoadTexture("assets/ui/button_base.png");
    buttonHoverTexture = LoadTexture("assets/ui/button_hover.png");
    textBoxTexture = LoadTexture("assets/ui/text_box.png");
    actionSelectionTexture = LoadTexture("assets/ui/action_selection_box.png");
    attackSelectionBoxTexture = LoadTexture("assets/ui/attack_selection_box.png");

    playerHud.rect = { 20, 200, (float)playerHud.hudTexture.width, 
        (float)playerHud.hudTexture.height };
    enemyHud.rect = { 400, 20, (float)enemyHud.hudTexture.width, 
        (float)enemyHud.hudTexture.height };
    playerHud.SetData(playerUnit, playerHud.rect);
    enemyHud.SetData(enemyUnit, enemyHud.rect);

    textBox = { 20, 350, (float)textBoxTexture.width, (float)textBoxTexture.height };
    attackSelectionBox = { 400, 350, (float)attackSelectionBoxTexture.width, 
        (float)attackSelectionBoxTexture.height };
    actionSelectionBox = { 20, 350, (float)actionSelectionTexture.width, 
        (float)actionSelectionTexture.height };

    dialogueBox = new BattleDialogueBox(textBox, textBoxTexture, font);
}

BattleUI::~BattleUI()
{
    UnloadTexture(playerHud.hudTexture);
    UnloadTexture(enemyHud.hudTexture);
    UnloadTexture(buttonBaseTexture);
    UnloadTexture(buttonHoverTexture);
    UnloadTexture(textBoxTexture);
    UnloadTexture(attackSelectionBoxTexture);
    UnloadTexture(actionSelectionTexture);

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
        playerHud.Draw();
        enemyHud.Draw();
        PlayerActionDraw();
        break;

    case BattleFlowState::PLAYER_TURN:
        playerHud.Draw();
        enemyHud.Draw();
        PlayerTurnDraw();
        break;

    case BattleFlowState::ENEMY_TURN:
        playerHud.Draw();
        enemyHud.Draw();
        PlayerTurnDraw();
        break;

    case BattleFlowState::WON:
        playerHud.Draw();
        playerUnit.Draw();
        break;

    case BattleFlowState::LOST:
        playerHud.Draw();
        enemyHud.Draw();
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
        DrawTextureRec(actionSelectionTexture, actionSelectionBox, 
            {actionSelectionBox.x, actionSelectionBox.y}, WHITE);
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
        playerUnit.Draw();
        enemyUnit.Draw();
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