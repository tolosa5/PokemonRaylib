#include "Battle.hpp"

Battle::Battle(std::vector<Pokemon> playerParty, 
    std::vector<Pokemon> enemyParty, BattleType battleType, Font font) 
    : battleUI(*this, font)
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

    std::string dialogue = currentBattleType == BattleType::WILD ? 
        "A wild " + enemyUnit.GetPokemon()->species->name + " appeared!" :
        "Trainer sent out " + enemyUnit.GetPokemon()->species->name + "!";

    battleUI.dialogueBox.SetDialogue(dialogue);
}

void Battle::Update()
{
    battleUI.Update();
}

void Battle::Draw()
{
    battleUI.Draw();
    switch (currentBattleState)
    {
    case BattleFlowState::NONE:
        /* code */
        break;

    case BattleFlowState::START:
        /* code */
        break;

    case BattleFlowState::DECISION_TIME:
        playerUnit.Draw();
        enemyUnit.Draw();
        break;

    case BattleFlowState::PLAYER_TURN:
        playerUnit.Draw();
        enemyUnit.Draw();
        break;

    case BattleFlowState::ENEMY_TURN:
        playerUnit.Draw();
        enemyUnit.Draw();
        break;

    case BattleFlowState::BUSY:
        playerUnit.Draw();
        enemyUnit.Draw();
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
}

#pragma region Battle Logic

void Battle::StartDialogueAndAnimation(
    const std::string& dialogue, float animationDuration)
{
    if (currentBattleType == BattleType::WILD)
    {
        
    }
    
}

void Battle::PlayerUseItem()
{
    
}

void Battle::HandleEnemyTurn()
{
    DamageHandling(*enemyUnit.GetPokemon(), *playerUnit.GetPokemon(), 
        enemyUnit.GetPokemon()->moves[0], false);
}

void Battle::ChangePokemon(Pokemon& newPokemon)
{
    playerUnit.SetUp(&newPokemon, true);
}

void Battle::EnemyLosePokemon()
{
    std::vector<Pokemon>& aliveEnemyParty = enemyParty;
    for (auto& pokemon : enemyParty)
    {
        if (pokemon.isFainted())
        {
            aliveEnemyParty.erase(std::remove(
                aliveEnemyParty.begin(), aliveEnemyParty.end(), pokemon), 
                aliveEnemyParty.end());
        }
    }

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
    StartDialogueAndAnimation(dialogue, 2.0f);
}

void Battle::DamageHandling(Pokemon& attacker, Pokemon& target, 
    Move& move, bool isPlayerAttacking)
{
    DamageDetails details = target.TakeDamage(move, attacker);
    
    if (details.critical)
        std::cout << "A critical hit!" << std::endl;

    if (details.typeEffectiveness > 1.0f)
        std::cout << "It's super effective!" << std::endl;
    else if (details.typeEffectiveness < 1.0f)
        std::cout << "It's not very effective..." << std::endl;

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

}

void Battle::BagButtonClick()
{
    
}

void Battle::OpenPkmnTab(bool postFainted)
{
    
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