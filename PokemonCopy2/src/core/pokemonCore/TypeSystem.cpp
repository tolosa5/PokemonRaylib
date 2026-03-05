#include "TypeSystem.hpp"
#include "src/managers/DataManager.hpp"

float TypeSystem::typeChart[static_cast<int>(Type::COUNT)]
    [static_cast<int>(Type::COUNT)] = {};

void TypeSystem::InitTypeChart(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
        return;

    json j;
    file >> j;

    for(int i = 0; i < static_cast<int>(Type::COUNT); ++i)
    {
        for(int k = 0; k < static_cast<int>(Type::COUNT); ++k)
        {
            typeChart[i][k] = 1.0f; // default effectiveness
        }
    }

    for (const auto& [atkTypeStr, defense] : j["chart"].items())
    {
        Type atkType = DataManager::GetInstance().StringToType(atkTypeStr);

        for (const auto& [defTypeStr, value] : defense.items())
        {
            Type defType = DataManager::GetInstance().StringToType(defTypeStr);
            typeChart[(int)atkType][(int)defType] = value;
        }
    }
}

float TypeSystem::GetEffectiveness(Type attackType, 
    Type defenseType, Type secondaryDefenseType)
{
    float multiplier = typeChart[(int)attackType][(int)defenseType];
    if (secondaryDefenseType != Type::NONE)
    {
        float secondaryMultiplier = typeChart[(int)attackType][(int)secondaryDefenseType];
        multiplier *= secondaryMultiplier;
    }
    return multiplier;
}