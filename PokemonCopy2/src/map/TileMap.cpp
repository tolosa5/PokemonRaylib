#include "TileMap.hpp"
#include <cstddef>

TileMap::TileMap(float gridSize, unsigned width, unsigned height)
{
    gridSizeF = gridSize;
    gridSizeU = static_cast<unsigned>(gridSizeF);
    maxSize = { (float)width, (float)height };
    layers = 2;

    map.resize(maxSize.x);
    for (size_t x = 0; x < maxSize.x; x++)
    {
        map.push_back(std::vector<std::vector<Tile*>>());

        for (size_t y = 0; y < maxSize.y; y++)
        {
            map[x].resize(maxSize.y);
            map[x].push_back(std::vector<Tile*>());

            for (size_t z = 0; z < layers; z++) // Assuming 3 layers of tiles
            {
                map[x][y].resize(layers);
                map[x][y].push_back(new Tile(x * gridSizeF, y * gridSizeF, gridSizeF));
            } 
        }
    }
}

TileMap::~TileMap()
{
    for (size_t x = 0; x < map.size(); x++)
    {
        for (size_t y = 0; y < map[x].size(); y++)
        {
            for (size_t z = 0; z < map[x][y].size(); z++)
            {
                delete map[x][y][z];
            }
        }
    }
}

void TileMap::Update()
{
    
}

void TileMap::Draw()
{
    for (auto& column : map)
    {
        for (auto& row : column)
        {
            for (auto& tile : row)
            {
                if (tile != nullptr)
                    tile->Draw();
            }
        }
    }
}

void TileMap::AddTile(const unsigned x, const unsigned y, const unsigned z)
{
    if (x < map.size() && x >= 0 && 
        y < map[0].size() && y >= 0 &&
        z < layers && z >= 0)
    {
        if (map[x][y][z] == nullptr)
            map[x][y][z] = new Tile(x * gridSizeF, y * gridSizeF, gridSizeF);
    }
    
}

void TileMap::RemoveTile(const unsigned x, const unsigned y, const unsigned z)
{
    // Implementation for removing a tile at the specified position and layer
    if (x < map.size() && x >= 0 && 
        y < map[0].size() && y >= 0 &&
        z < layers && z >= 0)
    {
        if (map[x][y][z] != nullptr)
        {
            delete map[x][y][z];
            map[x][y][z] = nullptr;
        }
    }
}

