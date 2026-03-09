#include "DataManager.hpp"
#include "src/core/pokemonCore/Pokemon.hpp"
#include "src/core/pokemonCore/PokemonSpecies.hpp"
#include "src/core/pokemonCore/MoveData.hpp"

DataManager::DataManager() = default;

void DataManager::LoadAll()
{
    LoadMoveData("assets/moves.json");
    LoadPokemonSpeciesData("assets/pokemon_species.json");
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
        moveData.name = value["ename"];
        moveData.type = StringToType(value["type"]);
        moveData.power = value["power"];
        moveData.accuracy = value["accuracy"];
        moveData.pp = value["pp"];
        moveData.category = StringToMoveCategory(value["category"]);

        moveMap[moveData.id] = moveData;
    }
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
        species.name = value["name"]["english"];
        species.type1 = StringToType(value["type"]);
        
        if (value.contains("type2"))
            species.type2 = StringToType(value["type2"]);

        species.baseStats.hp = value["base"]["HP"];
        species.baseStats.attack = value["base"]["Attack"];
        species.baseStats.defense = value["base"]["Defense"];
        species.baseStats.specialAttack = value["base"]["Sp. Attack"];
        species.baseStats.specialDefense = value["base"]["Sp. Defense"];
        species.baseStats.speed = value["base"]["Speed"];

        /*
        // not working, learnableMoves is empty
        for (const auto& moveId : value["learnableMoves"])
        {
            const MoveData& moveData = GetMoveById(moveId);
            species.learnableMoves.push_back(moveData);
        }
        */

        pokemonSpeciesMap[species.id] = species;
    }
}

void DataManager::LoadDialogues(const std::string& filePath)
{
    std::ifstream file(filePath);
    json dialogueJson;
    file >> dialogueJson;

    for (const auto& [key, value] : dialogueJson.items())
    {
        dialogueMap[key] = value;
    }
}

Pokemon* DataManager::CreatePokemon(int speciesId, int level)
{
    const PokemonSpecies& species = GetPokemonSpeciesById(speciesId);

    Pokemon* pokemon = new Pokemon(const_cast<PokemonSpecies*>(&species), level);
    pokemon->CalculateStats();

    if (species.learnableMoves.empty())
        return pokemon;
    
    for (size_t i = 0; i < 4 && i < species.learnableMoves.size(); ++i)
    {
        const MoveData& moveData = GetMoveById(species.learnableMoves[i].id);
        
        Move moveInstance = Move(&moveData);
        pokemon->moves.push_back(moveInstance);
    }

    return pokemon;
}

void DataManager::WritePokemonToFile(const Pokemon& pokemon, const std::string& filePath)
{
    json j;
    j["speciesId"] = pokemon.species->id;
    j["level"] = pokemon.level;
    j["currentHP"] = pokemon.currentHP;

    std::ofstream file(filePath);
    file << j.dump(4);
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