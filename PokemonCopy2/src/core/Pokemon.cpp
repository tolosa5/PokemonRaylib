#include "Pokemon.hpp"

Pokemon::Pokemon()
    : species(nullptr),
      level(1),
      currentHP(0),
      stats{0, 0, 0, 0, 0, 0},
      ivs{0, 0, 0, 0, 0, 0},
      evs{0, 0, 0, 0, 0, 0}
{
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
    stats.attack = CalculateNonHpStat(base.attack, ivs.attack, evs.attack, level);
    stats.defense = CalculateNonHpStat(base.defense, ivs.defense, evs.defense, level);
    stats.specialAttack = CalculateNonHpStat(base.specialAttack, ivs.specialAttack, evs.specialAttack, level);
    stats.specialDefense = CalculateNonHpStat(base.specialDefense, ivs.specialDefense, evs.specialDefense, level);
    stats.speed = CalculateNonHpStat(base.speed, ivs.speed, evs.speed, level);

    currentHP = stats.hp;
}