#ifndef DATAMANAGER_HPP
#define DATAMANAGER_HPP

#include <unordered_map>
#include "src/core/Pokemon.hpp"
#include "src/core/PokemonSpecies.hpp"
#include "src/core/MoveData.hpp"
#include "nlohmann/json.hpp"
#include <fstream>

using json = nlohmann::json;

class DataManager
{
public:

    DataManager();
    ~DataManager();

    const PokemonSpecies& GetPokemonSpeciesById(int id) const;
    const MoveData& GetMoveById(int id) const;

private:
    std::unordered_map<int, PokemonSpecies> pokemonSpeciesMap;
    std::unordered_map<int, MoveData> moveMap;

    void LoadAll();
    void LoadPokemonSpeciesData(const std::string& filePath);
    void LoadMoveData(const std::string& filePath);

    Pokemon* CreatePokemon(int speciesId, int level);

    Type StringToType(const std::string& typeStr) const;
    MoveCategory StringToMoveCategory(const std::string& categoryStr) const;
};

#endif