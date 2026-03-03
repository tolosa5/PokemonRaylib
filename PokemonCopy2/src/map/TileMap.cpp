#include "TileMap.hpp"

void TileMap::ClearMap()
{
    for (size_t x = 0; x < map.size(); x++)
    {
        for (size_t y = 0; y < map[x].size(); y++)
        {
            for (size_t z = 0; z < map[x][y].size(); z++)
            {
                delete map[x][y][z];
                map[x][y][z] = nullptr;
            }
            map[x][y].clear();
        }
        map[x].clear();
    }
    map.clear();
}

TileMap::TileMap(float gridSize, unsigned width, unsigned layer, std::string textureFile)
{
    gridSizeF = gridSize;
    gridSizeU = static_cast<unsigned>(gridSizeF);
    maxSize = { (float)width, (float)layer };
    this->textureFile = textureFile;
    layers = 1;

    map.resize(static_cast<size_t>(maxSize.x),
        std::vector<std::vector<Tile*>>(static_cast<size_t>(maxSize.y),
            std::vector<Tile*>(layers, nullptr)));

    tileTextureSheet = LoadTexture(textureFile.c_str());
    
}

TileMap::~TileMap()
{
    ClearMap();
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
    const unsigned z, const Rectangle& sourceRect, 
    const bool collision, const short type)
{
    if (x < maxSize.x &&
        y < maxSize.y &&
        z < layers)
    {
        if (map[x][y][z] == nullptr)
        {
            std::cout << "Added tile at: " << x << ", " << y << std::endl;
            map[x][y][z] = new Tile(x, y, gridSizeF, tileTextureSheet, 
                sourceRect, collision, type);
        }
    }
}

void TileMap::RemoveTile(const unsigned x, const unsigned y, const unsigned z)
{
    if (x < maxSize.x &&
        y < maxSize.y &&
        z < layers)
    {
        if (map[x][y][z] != nullptr)
        {
            delete map[x][y][z];
            map[x][y][z] = nullptr;
        }
    }
}

void TileMap::SaveToFile(const std::string& filename)
{
    /*
    Format:
    Size x y
    gridSize
    layers
    texture file

    gridPos x y
    layer
    Texture rect x y 
    collision
    type
    */

    std::ofstream out_file;
    out_file.open(filename);
    if (out_file.is_open())
    {
        out_file << maxSize.x << " " << maxSize.y << "\n"
            << gridSizeU << "\n"
            << layers << "\n"
            << textureFile << "\n";

        for (size_t x = 0; x < map.size(); x++)
        {
            for (size_t y = 0; y < map[x].size(); y++)
            {
                for (size_t z = 0; z < map[x][y].size(); z++)
                {
                    if (map[x][y][z])
                        out_file << x << " " << y << " " << z << " " <<  
                            map[x][y][z]->GetAsString() << " ";
                }
            }
        }
    }
    else
    {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
    }
    
    out_file.close();
}

void TileMap::LoadFromFile(const std::string& filename)
{
    std::ifstream in_file;
    in_file.open(filename);

    if (in_file.is_open())
    {
        Vector2 size;
        unsigned gridSize = 0;
        unsigned layers = 0;
        std::string textureFile = "";
        unsigned x = 0, y = 0, z = 0;
        float trX = 0.f;
        float trY = 0.f;
        bool collision = false;
        short type = 0;

        in_file >> size.x >> size.y >> gridSize >> layers >> textureFile;

        gridSizeF = static_cast<float>(gridSize);
        gridSizeU = gridSize;
        maxSize.x = size.x;
        maxSize.y = size.y;
        this->layers = layers;
        this->textureFile = textureFile;

        ClearMap();

        map.resize(static_cast<size_t>(maxSize.x),
            std::vector<std::vector<Tile*>>(static_cast<size_t>(maxSize.y),
                std::vector<Tile*>(this->layers, nullptr)));

        UnloadTexture(tileTextureSheet);

        tileTextureSheet = LoadTexture(textureFile.c_str());

        while (in_file >> x >> y >> z >> trX >> trY >> collision >> type)
        {
            if (x < maxSize.x && y < maxSize.y && z < this->layers)
            {
                map[x][y][z] = new Tile(x, y, gridSizeF, tileTextureSheet,
                    Rectangle
                    {
                        trX, trY, gridSizeF, gridSizeF
                    },
                    collision, type);
            }
        }
    }
    else
    {
        std::cerr << "Error opening file for loading: " << filename << std::endl;
    }

    in_file.close();
}

