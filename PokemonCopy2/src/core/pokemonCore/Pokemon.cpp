#include "Pokemon.hpp"

Pokemon::Pokemon(PokemonSpecies* species, int level)
    : species(species), level(level)
{
    stats = {0, 0, 0, 0, 0, 0};
    ivs = {0, 0, 0, 0, 0, 0};
    evs = {0, 0, 0, 0, 0, 0};
}
      

Pokemon::~Pokemon() = default;

void Pokemon::CalculateStats()
{
    if (!species)
    {
        stats = {0, 0, 0, 0, 0, 0};
        currentHP = 0;
        return;
    }

    const Stats& base = species->baseStats;

    stats.hp = CalculateHpStat(base.hp, ivs.hp, evs.hp, level);
    stats.attack = CalculateNonHpStat(
        base.attack, ivs.attack, evs.attack, level);
    stats.defense = CalculateNonHpStat(
        base.defense, ivs.defense, evs.defense, level);
    stats.specialAttack = CalculateNonHpStat(
        base.specialAttack, ivs.specialAttack, evs.specialAttack, level);
    stats.specialDefense = CalculateNonHpStat(
        base.specialDefense, ivs.specialDefense, evs.specialDefense, level);
    stats.speed = CalculateNonHpStat(
        base.speed, ivs.speed, evs.speed, level);

    currentHP = stats.hp;
}

DamageDetails Pokemon::TakeDamage(Move& move, Pokemon& attacker)
{
    float critical = 1.0f;
    if (GetRandomValue(0, 100) < 6.25)
        critical = 2.0f;

    float typeEffectiveness = TypeSystem::GetEffectiveness(
        move.data->type, species->type1, species->type2);
    
    DamageDetails damageDetails = DamageDetails
    {
        critical,
        typeEffectiveness,
        false
    };

    float modifiers = critical * typeEffectiveness * (GetRandomValue(85, 101) / 100.0f);
    
    MoveCategory moveCategory = move.data->category;
    int usedDefense = moveCategory == MoveCategory::Special
        ? stats.specialDefense
        : stats.defense;

    int usedAttack = moveCategory == MoveCategory::Special
        ? attacker.stats.specialAttack
        : attacker.stats.attack;

    float a = (2 * attacker.level + 10) / 250.0f;
    float d = a * move.data->power * ((float)usedAttack / usedDefense) + 2;

    int damage = static_cast<int>(d * modifiers);

    currentHP -= damage;
    if (currentHP < 0)
    {
        currentHP = 0;
        damageDetails.fainted = true;
    }

    return damageDetails;
}