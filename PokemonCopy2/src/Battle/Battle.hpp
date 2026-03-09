#ifndef BATTLE_HPP
#define BATTLE_HPP

#include "src/ui/ButtonGroup.hpp"
#include "BattleUnit.hpp"
#include "BattleUI.hpp"
#include <map>
#include <vector>

enum class BattleFlowState
{
    NONE,
    START,
    DECISION_TIME,
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

    Rectangle textBox;
    Rectangle attackSelectionBox;
    Rectangle playerInfoBox;
    Rectangle enemyInfoBox;

    Texture2D buttonBaseTexture;
    Texture2D buttonHoverTexture;
    Texture2D textBoxTexture;
    Texture2D attackSelectionBoxTexture;
    Texture2D playerInfoBoxTexture;
    Texture2D enemyInfoBoxTexture;

    std::map<std::string, Button*> buttons;
    ButtonGroup* startButtonGroup;
    ButtonGroup* battleButtonGroup;
    ButtonGroup* bagStartButtonGroup;
    std::vector<Button*> startButtonVector;
    std::vector<Button*> battleButtonVector;
    std::vector<Button*> bagStartButtonVector;

    BattleFlowState currentBattleState;
    BattleType currentBattleType;

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
    BattleUI battleUI;


    void StartDialogueAndAnimation(
        const std::string& dialogue, float animationDuration);
    void HandleEnemyTurn();
    void PlayerUseItem();
    void ChangePokemon(Pokemon& newPokemon);
    void EnemyLosePokemon();
    void EnemyChangePokemon(std::vector<Pokemon>& aliveEnemyParty);
    void DamageHandling(Pokemon& attacker, Pokemon& target, 
        Move& move, bool isPlayerAttacking);
    void PlayerPokemonFainted(Pokemon& faintedPokemon);
    void EnemyPokemonFainted(Pokemon& faintedPokemon);
    void EndBattle(EndBattleReason endReason);
};

#endif