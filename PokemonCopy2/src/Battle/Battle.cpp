#include "Battle.hpp"

Battle::Battle(std::vector<Pokemon> playerParty, 
    std::vector<Pokemon> enemyParty, BattleType battleType, Font font) 
    : battleUI(*this, font, playerUnit, enemyUnit)
{
    this->playerParty = playerParty;
    this->enemyParty = enemyParty;
    this->currentBattleType = battleType;
    BattleStart();
}

Battle::~Battle()
{
    
}

void Battle::BattleStart()
{
    this->currentBattleState = BattleFlowState::START;

    playerUnit.SetUp(&this->playerParty[0], true);
    enemyUnit.SetUp(&this->enemyParty[0], false);

    battleUI.playerHud.SetData(playerUnit, battleUI.playerHudRect);
    battleUI.enemyHud.SetData(enemyUnit, battleUI.enemyHudRect);

    playerUnit.SetActive(false);
    enemyUnit.SetActive(true);

    WaitTime(1.0f);

    std::string dialogue = currentBattleType == BattleType::WILD ? 
        "A wild " + enemyUnit.GetPokemon()->species->name + " appeared!" :
        "Trainer sent out " + enemyUnit.GetPokemon()->species->name + "!";

    actionQueue.push(std::make_unique<BattleTextAction>(
        dialogue, battleUI.dialogueBox, 2.0f));

    std::string playerDialogue = "Go! " + playerUnit.GetPokemon()->species->name + "!";
    actionQueue.push(std::make_unique<BattleTextAction>(
        playerDialogue, battleUI.dialogueBox, 1.5f));

    playerUnit.SetActive(true);
    currentBattleState = BattleFlowState::PLAYER_ACTION;
    currentPlayerAction = PlayerAction::IDLE;
    startButtonGroup->SetActive(true);
}

void Battle::Update()
{
    battleUI.Update();
    if (!currentAction && !actionQueue.empty())
    {
        currentAction = actionQueue.front().release();
        actionQueue.pop();
        currentAction->Start();
    }

    if (currentAction)
    {
        currentAction->Update();
        if (currentAction->Finished())
        {
            delete currentAction;
            currentAction = nullptr;
        }
    }
}

void Battle::Draw()
{
    battleUI.Draw(currentBattleState);
}

#pragma region Battle Logic

void Battle::StartAnimation()
{
    
}

void Battle::SpeedTiers(Pokemon& playerPokemon, Pokemon& enemyPokemon)
{
    if (playerPokemon.stats.speed > enemyPokemon.stats.speed)
        currentBattleState = BattleFlowState::PLAYER_TURN;
    else
    {
        currentBattleState = BattleFlowState::ENEMY_TURN;
        HandleEnemyTurn(enemyUnit.GetPokemon()->moves[0]);
    }
}

void Battle::HandleEnemyTurn(Move selectedMove)
{
    WaitTime(1.0f);

    MoveData moveData = *selectedMove.data;
    std::string dialogue = "Enemy " + enemyUnit.GetPokemon()->species->name + 
        " used " + moveData.name + "!";
    battleUI.dialogueBox->SetDialogue(dialogue);

    currentDamageState = DamageState::START_ATTACK;
    DamageHandling(enemyUnit, playerUnit, selectedMove, false);
}

void Battle::PlayerUseItem()
{
    
}

void Battle::ChangePokemon(Pokemon& newPokemon)
{
    playerUnit.SetUp(&newPokemon, true);
}

void Battle::EnemyLosePokemon()
{
    std::vector<Pokemon>& aliveEnemyParty = enemyParty;
    aliveEnemyParty.erase(
        std::remove_if(aliveEnemyParty.begin(), aliveEnemyParty.end(),
            [](const Pokemon& pokemon)
            {
                return pokemon.isFainted();
            }),
        aliveEnemyParty.end());

    if (!aliveEnemyParty.empty())
        EnemyChangePokemon(aliveEnemyParty);
    else
        EndBattle(EndBattleReason::PLAYER_WON);
}

void Battle::EnemyChangePokemon(std::vector<Pokemon>& aliveEnemyParty)
{
    Pokemon& newPokemon = aliveEnemyParty[0];
    enemyUnit.SetUp(&newPokemon, false);
    std::string dialogue = "Trainer sent out " + newPokemon.species->name + "!";
    battleUI.dialogueBox->SetDialogue(dialogue);
}

void Battle::DamageHandling(BattleUnit& attacker, BattleUnit& target, 
    Move& move, bool isPlayerAttacking)
{
    Pokemon& attackerPokemon = *attacker.GetPokemon();
    Pokemon& targetPokemon = *target.GetPokemon();
    
    std::string dialogue = (isPlayerAttacking ? "Your " : "Enemy ") + 
        attackerPokemon.species->name + " used " + move.data->name + "!";

    actionQueue.push(std::make_unique<BattleTextAction>(
        dialogue, battleUI.dialogueBox, 1.5f));

    DamageDetails details = target.GetPokemon()->TakeDamage(move, attackerPokemon);

    actionQueue.push(std::make_unique<UpdateBarAction>(target));

    if (details.critical)
    {
        std::string dialogue = "A critical hit!";
        actionQueue.push(std::make_unique<BattleTextAction>(
            dialogue, battleUI.dialogueBox, 1));
    }

    if (details.typeEffectiveness > 1.0f)
    {
        std::string dialogue = "It's super effective!";
        actionQueue.push(std::make_unique<BattleTextAction>(
            dialogue, battleUI.dialogueBox, 1));
    }
    else if (details.typeEffectiveness < 1.0f)
    {
        std::string dialogue = "It's not very effective...";
        actionQueue.push(std::make_unique<BattleTextAction>(
            dialogue, battleUI.dialogueBox, 1));
    }

    if (details.fainted)
    {
        if (isPlayerAttacking)
            PlayerPokemonFainted(targetPokemon);
        else
            EnemyPokemonFainted(targetPokemon);
    }
}

void Battle::PlayerPokemonFainted(Pokemon& faintedPokemon)
{
    std::string dialogue = faintedPokemon.species->name + " fainted!";
    actionQueue.push(std::make_unique<BattleTextAction>(
        dialogue, battleUI.dialogueBox, 2.0f));

    for (auto& pokemon : playerParty)
    {
        if (!pokemon.isFainted())
        {
            OpenPkmnTab(true);
            return;
        }
    }

    EndBattle(EndBattleReason::ENEMY_WON);
}

void Battle::EnemyPokemonFainted(Pokemon& faintedPokemon)
{
    std::string dialogue = "Enemy " + faintedPokemon.species->name + " fainted!";
    actionQueue.push(std::make_unique<BattleTextAction>(
        dialogue, battleUI.dialogueBox, 2.0f));

    //Give exp, check for level up, etc.

    for (auto& pokemon : enemyParty)
    {
        if (!pokemon.isFainted())
        {
            EnemyLosePokemon();
            return;
        }
    }

    EndBattle(EndBattleReason::PLAYER_WON);
}

void Battle::EndBattle(EndBattleReason endReason)
{
    switch (endReason)
    {
    case EndBattleReason::PLAYER_FLED:
        // Handle player fleeing
        break;

    case EndBattleReason::PLAYER_WON:
        // Handle player victory
        break;

    case EndBattleReason::ENEMY_WON:
        // Handle enemy victory
        break;

    default:
        break;
    }

    // Clean up battle and return to previous state
}

#pragma endregion

#pragma region Button Clicks

void Battle::BattleButtonClick()
{
    currentPlayerAction = PlayerAction::ATTACK;
    startButtonGroup->SetActive(false);
    battleButtonGroup->SetActive(true);
}

void Battle::BagButtonClick()
{
    currentPlayerAction = PlayerAction::BAG;
    startButtonGroup->SetActive(false);
}

void Battle::OpenPkmnTab(bool postFainted)
{
    currentPlayerAction = PlayerAction::POKEMON;
    startButtonGroup->SetActive(false);
}

void Battle::RunButtonClick()
{
    if (currentBattleType == BattleType::TRAINER)
        return;
    
    EndBattleReason reason = EndBattleReason::PLAYER_FLED;
    EndBattle(reason);
}

void Battle::Attack1ButtonClick()
{
    DamageHandling(playerUnit, enemyUnit, 
        playerUnit.GetPokemon()->moves[0], true);
}

void Battle::Attack2ButtonClick()
{
    DamageHandling(playerUnit, enemyUnit, 
        playerUnit.GetPokemon()->moves[1], true);
}

void Battle::Attack3ButtonClick()
{
    DamageHandling(playerUnit, enemyUnit, 
        playerUnit.GetPokemon()->moves[2], true);
}

void Battle::Attack4ButtonClick()
{
    DamageHandling(playerUnit, enemyUnit, 
        playerUnit.GetPokemon()->moves[3], true);
}

#pragma endregion