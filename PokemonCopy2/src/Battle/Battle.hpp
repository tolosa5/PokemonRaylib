#ifndef BATTLE_HPP
#define BATTLE_HPP

#include "src/ui/ButtonGroup.hpp"
#include "BattleUnit.hpp"
#include <map>
#include <vector>

enum class BattleState
{
    NONE,
    START,
    PLAYER_TURN,
    ENEMY_TURN,
    BUSY,
    WON,
    LOST
};

enum class BattleType
{
    WILD,
    TRAINER
};

enum class EndBattleReason
{
    PLAYER_FLED,
    PLAYER_WON,
    ENEMY_WON
};

class Battle
{
public:
    BattleUnit playerUnit;
    BattleUnit enemyUnit;

    BattleState currentBattleState;
    BattleType currentBattleType;

    std::vector<Pokemon> playerParty;
    std::vector<Pokemon> enemyParty;

    Battle(std::vector<Pokemon> playerParty, 
        std::vector<Pokemon> enemyParty, BattleType battleType);
    ~Battle();

    void BattleStart();

    void Update();
    void Draw();

private:
    
    void InitButtons();

    void ChangePokemon(Pokemon& newPokemon);
    void HandlePlayerTurn();
    void HandleEnemyTurn();
    void DamageHandling(Pokemon& attacker, Pokemon& target, 
        Move& move, bool isPlayerAttacking);
    void PlayerPokemonFainted(Pokemon& faintedPokemon);
    void EnemyPokemonFainted(Pokemon& faintedPokemon);
    void EndBattle(EndBattleReason endReason);

    void BattleButtonClick();
    void BagButtonClick();
    void OpenPkmnTab(bool postFeinted = false);
    void RunButtonClick();
    void Attack1ButtonClick();
    void Attack2ButtonClick();
    void Attack3ButtonClick();
    void Attack4ButtonClick();
};

#endif