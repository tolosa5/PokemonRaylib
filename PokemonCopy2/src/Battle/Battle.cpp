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

    battleUI.dialogueBox->SetDialogue(dialogue);
    WaitTime(1.5f);
    //Throw pokemon
    playerUnit.SetActive(true);
    WaitTime(0.5f);
    currentBattleState = BattleFlowState::PLAYER_ACTION;
    currentPlayerAction = PlayerAction::IDLE;
    startButtonGroup->SetActive(true);
}

void Battle::Update()
{
    battleUI.Update();
    
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
    {
        currentBattleState = BattleFlowState::PLAYER_TURN;
    }
    else
    {
        currentBattleState = BattleFlowState::ENEMY_TURN;
        HandleEnemyTurn();
    }
}

void Battle::HandleEnemyTurn()
{
    WaitTime(1.0f);

    DamageHandling(*enemyUnit.GetPokemon(), *playerUnit.GetPokemon(), 
        enemyUnit.GetPokemon()->moves[0], false);
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

void Battle::DamageHandling(Pokemon& attacker, Pokemon& target, 
    Move& move, bool isPlayerAttacking)
{
    DamageDetails details = target.TakeDamage(move, attacker);
    
    if (details.critical)
    {
        std::string dialogue = "A critical hit!";
        battleUI.dialogueBox->SetDialogue(dialogue);

        WaitTime(0.5f);
    }

    if (details.typeEffectiveness > 1.0f)
    {
        std::string dialogue = "It's super effective!";
        battleUI.dialogueBox->SetDialogue(dialogue);

        WaitTime(0.5f);
    }
    else if (details.typeEffectiveness < 1.0f)
    {
        std::string dialogue = "It's not very effective...";
        battleUI.dialogueBox->SetDialogue(dialogue);

        WaitTime(0.5f);
    }

    if (details.fainted)
    {
        if (isPlayerAttacking)
            PlayerPokemonFainted(target);
        else
            EnemyPokemonFainted(target);
    }
}

void Battle::PlayerPokemonFainted(Pokemon& faintedPokemon)
{
    std::string dialogue = faintedPokemon.species->name + " fainted!";
    battleUI.dialogueBox->SetDialogue(dialogue);

    WaitTime(2.0f);

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
    battleUI.dialogueBox->SetDialogue(dialogue);

    WaitTime(2.0f);

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
    DamageHandling(*playerUnit.GetPokemon(), *enemyUnit.GetPokemon(), 
        playerUnit.GetPokemon()->moves[0], true);
}

void Battle::Attack2ButtonClick()
{
    DamageHandling(*playerUnit.GetPokemon(), *enemyUnit.GetPokemon(), 
        playerUnit.GetPokemon()->moves[1], true);
}

void Battle::Attack3ButtonClick()
{
    DamageHandling(*playerUnit.GetPokemon(), *enemyUnit.GetPokemon(), 
        playerUnit.GetPokemon()->moves[2], true);
}

void Battle::Attack4ButtonClick()
{
    DamageHandling(*playerUnit.GetPokemon(), *enemyUnit.GetPokemon(), 
        playerUnit.GetPokemon()->moves[3], true);
}

#pragma endregion