#ifndef BATTLE_HPP
#define BATTLE_HPP

#include "src/ui/ButtonGroup.hpp"
#include "BattleUnit.hpp"
#include "BattleUI.hpp"
#include "BattleAction.hpp"
#include "BattleTextAction.hpp"
#include "UpdateBarAction.hpp"
#include "src/utils/WaitUntil.hpp"
#include <queue>
#include <memory>
#include <map>
#include <vector>

enum class BattleFlowState
{
    NONE,
    START,
    PLAYER_ACTION,
    PLAYER_TURN,
    ENEMY_TURN,
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

enum class PlayerAction
{
    IDLE,
    ATTACK,
    BAG,
    POKEMON,
    TURN
};

class Battle
{
public:
    std::queue<std::unique_ptr<BattleAction>> actionQueue;
    BattleAction* currentAction = nullptr;

    BattleUnit playerUnit;
    BattleUnit enemyUnit;

    BattleUI battleUI;
    
    std::map<std::string, Button*> buttons;
    ButtonGroup* startButtonGroup;
    ButtonGroup* battleButtonGroup;
    ButtonGroup* bagStartButtonGroup;
    std::vector<Button*> startButtonVector;
    std::vector<Button*> battleButtonVector;
    std::vector<Button*> bagStartButtonVector;

    BattleFlowState currentBattleState;
    BattleType currentBattleType;
    PlayerAction currentPlayerAction;

    std::vector<Pokemon> playerParty;
    std::vector<Pokemon> enemyParty;

    Battle(std::vector<Pokemon> playerParty, 
        std::vector<Pokemon> enemyParty, BattleType battleType, 
        Font font);
    ~Battle();

    void BattleStart();

    void Update();
    void Draw();

    void BattleButtonClick();
    void BagButtonClick();
    void OpenPkmnTab(bool postFainted = false);
    void RunButtonClick();
    void Attack1ButtonClick();
    void Attack2ButtonClick();
    void Attack3ButtonClick();
    void Attack4ButtonClick();

private:
    
    void StartAnimation();
    void HandleEnemyTurn(Move selectedMove);
    void SpeedTiers(Pokemon& playerPokemon, Pokemon& enemyPokemon);
    void PlayerUseItem();
    void ChangePokemon(Pokemon& newPokemon);
    void EnemyLosePokemon();
    void EnemyChangePokemon(std::vector<Pokemon>& aliveEnemyParty);
    void DamageHandling(BattleUnit& attacker, BattleUnit& target, 
        Move& move, bool isPlayerAttacking);
    void PlayerPokemonFainted(Pokemon& faintedPokemon);
    void EnemyPokemonFainted(Pokemon& faintedPokemon);
    void EndBattle(EndBattleReason endReason);
};

#endif