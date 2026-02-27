#include "TileMap.hpp"

TileMap::TileMap(float gridSize, unsigned width, unsigned layer)
{
    gridSizeF = gridSize;
    gridSizeU = static_cast<unsigned>(gridSizeF);
    maxSize = { (float)width, (float)layer };
    layers = 1;

    map.resize(maxSize.x, std::vector<std::vector<Tile*>>());
    for (size_t x = 0; x < maxSize.x; x++)
    {
        for (size_t y = 0; y < maxSize.y; y++)
        {
            map[x].resize(maxSize.y, std::vector<Tile*>());
            for (size_t z = 0; z < layers; z++)
            {
                map[x][y].resize(layers, nullptr);
            }
        }
    }

    tileTextureSheet = LoadTexture("assets/graphics/sprites/tileset.png");
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
    UnloadTexture(tileTextureSheet);
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

void TileMap::AddTile(const unsigned x, const unsigned y, 
    const unsigned z, const Rectangle& sourceRect)
{
    if (x < maxSize.x && x >= 0 && 
        y < maxSize.y && y >= 0 &&
        z < layers && z >= 0)
    {
        if (map[x][y][z] == nullptr)
        {
            std::cout << "Added tile at: " << x << ", " << y << std::endl;
            map[x][y][z] = new Tile(x * gridSizeF, y * gridSizeF, 
                gridSizeF, tileTextureSheet, sourceRect );
        }
    }
}

void TileMap::RemoveTile(const unsigned x, const unsigned y, const unsigned z)
{
    if (x < maxSize.x && x >= 0 && 
        y < maxSize.y && y >= 0 &&
        z < layers && z >= 0)
    {
        if (map[x][y][z] != nullptr)
        {
            delete map[x][y][z];
            map[x][y][z] = nullptr;
        }
    }
}

unsigned TileMap::GetSheetColumns(float tileWidth) const
{
    if (tileWidth <= 0.f)
        return 1;

    const unsigned columns = static_cast<unsigned>(tileTextureSheet.width / tileWidth);
    return columns > 0 ? columns : 1;
}

unsigned TileMap::GetSheetRows(float tileHeight) const
{
    if (tileHeight <= 0.f)
        return 1;

    const unsigned rows = static_cast<unsigned>(tileTextureSheet.height / tileHeight);
    return rows > 0 ? rows : 1;
}

