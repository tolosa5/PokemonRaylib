#ifndef TYPESYSTEM_HPP
#define TYPESYSTEM_HPP

#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

enum class Type
{
    Normal,
    Fire,
    Water,
    Grass,
    Electric,
    Ice,
    Fighting,
    Poison,
    Ground,
    Flying,
    Psychic,
    Bug,
    Rock,
    Ghost,
    Dragon,
    Dark,
    Steel,
    NONE,
    COUNT = 18
};

class TypeSystem
{
public:
    static void InitTypeChart(const std::string& filePath);
    static float GetEffectiveness(
        Type attackType, Type defenseType, 
        Type secondaryDefenseType = Type::NONE);

private:
    static float typeChart[static_cast<int>(Type::COUNT)]
        [static_cast<int>(Type::COUNT)];
};

#endif