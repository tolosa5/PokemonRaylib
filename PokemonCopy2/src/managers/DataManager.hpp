#ifndef DATAMANAGER_HPP
#define DATAMANAGER_HPP

#include <unordered_map>
#include "src/core/pokemonCore/Pokemon.hpp"
#include "src/core/pokemonCore/PokemonSpecies.hpp"
#include "src/core/pokemonCore/MoveData.hpp"
#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

class DataManager
{
public:

    static DataManager& GetInstance()
    {
        static DataManager instance;
        return instance;
    }

    DataManager();

    void LoadAll();
    void LoadMoveData(const std::string& filePath);
    void LoadPokemonSpeciesData(const std::string& filePath);
    void LoadTypeChartData(const std::string& filePath);

    Pokemon* CreatePokemon(int speciesId, int level);
    Pokemon GenerateWildPokemon(int speciesId, int level);

    Type StringToType(const std::string& typeStr) const;
    MoveCategory StringToMoveCategory(
        const std::string& categoryStr) const;
    
    const PokemonSpecies& GetPokemonSpeciesById(int id) const;
    const MoveData& GetMoveById(int id) const;
    
private:
    
    ~DataManager() = default;
    DataManager(const DataManager&) = delete;
    DataManager& operator=(const DataManager&) = delete;

    std::unordered_map<int, PokemonSpecies> pokemonSpeciesMap;
    std::unordered_map<int, MoveData> moveMap;
};

#endif