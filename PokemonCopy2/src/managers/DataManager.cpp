#include "DataManager.hpp"

DataManager::DataManager()
{

}

DataManager::~DataManager()
{

}

void DataManager::LoadAll()
{
    LoadPokemonSpeciesData("assets/pokemon_species.json");
    LoadMoveData("assets/moves.json");
}

void DataManager::LoadPokemonSpeciesData(const std::string& filePath)
{
    std::ifstream file(filePath);
    json pokemonJson;
    file >> pokemonJson;

    for (const auto& [id, value] : pokemonJson.items())
    {
        PokemonSpecies species;
        
        species.id = value["id"];
        species.name = value["name"];
        species.type1 = StringToType(value["type"]);
        
        if (value.contains("type2"))
            species.type2 = StringToType(value["type2"]);

        species.baseStats.hp = value["baseStats"]["hp"];
        species.baseStats.attack = value["baseStats"]["attack"];
        species.baseStats.defense = value["baseStats"]["defense"];
        species.baseStats.specialAttack = value["baseStats"]["specialAttack"];
        species.baseStats.specialDefense = value["baseStats"]["specialDefense"];
        species.baseStats.speed = value["baseStats"]["speed"];

        // not working, learnableMoves is empty
        for (const auto& moveId : value["learnableMoves"])
        {
            const MoveData& moveData = GetMoveById(moveId);
            species.learnableMoves.push_back(moveData);
        }

        pokemonSpeciesMap[species.id] = species;
    }
}

void DataManager::LoadMoveData(const std::string& filePath)
{
    std::ifstream file(filePath);
    json moveJson;
    file >> moveJson;

    for (const auto& [id, value] : moveJson.items())
    {
        MoveData moveData;
        
        moveData.id = value["id"];
        moveData.name = value["name"];
        moveData.type = StringToType(value["type"]);
        moveData.power = value["power"];
        moveData.accuracy = value["accuracy"];
        moveData.pp = value["pp"];
        moveData.category = StringToMoveCategory(value["category"]);

        moveMap[moveData.id] = moveData;
    }
}

Pokemon* DataManager::CreatePokemon(int speciesId, int level)
{
    const PokemonSpecies& species = GetPokemonSpeciesById(speciesId);

    Pokemon* pokemon = new Pokemon(const_cast<PokemonSpecies*>(&species), level);
    pokemon->CalculateStats();

    if (species.learnableMoves.empty())
        return pokemon;
    
    for (int i = 0; i < 4 && i < species.learnableMoves.size(); ++i)
    {
        const MoveData& moveData = GetMoveById(species.learnableMoves[i].id);
        
        Move moveInstance = Move(&moveData);
        pokemon->moves.push_back(moveInstance);
    }

    return pokemon;
}

Type DataManager::StringToType(const std::string& typeStr) const
{
    std::unordered_map<std::string, Type> typeMap = {
        {"Normal", Type::Normal},
        {"Fire", Type::Fire},
        {"Water", Type::Water},
        {"Grass", Type::Grass},
        {"Electric", Type::Electric},
        {"Ice", Type::Ice},
        {"Fighting", Type::Fighting},
        {"Poison", Type::Poison},
        {"Ground", Type::Ground},
        {"Flying", Type::Flying},
        {"Psychic", Type::Psychic},
        {"Bug", Type::Bug},
        {"Rock", Type::Rock},
        {"Ghost", Type::Ghost},
        {"Dragon", Type::Dragon},
        {"Dark", Type::Dark},
        {"Steel", Type::Steel}
    };

    return typeMap.at(typeStr);
}

MoveCategory DataManager::StringToMoveCategory(const std::string& categoryStr) const
{
    std::unordered_map<std::string, MoveCategory> categoryMap = {
        {"Physical", MoveCategory::Physical},
        {"Special", MoveCategory::Special},
        {"Status", MoveCategory::Status}
    };

    return categoryMap.at(categoryStr);
}

const PokemonSpecies& DataManager::GetPokemonSpeciesById(int id) const
{
    return pokemonSpeciesMap.at(id);
}

const MoveData& DataManager::GetMoveById(int id) const
{
    return moveMap.at(id);
}