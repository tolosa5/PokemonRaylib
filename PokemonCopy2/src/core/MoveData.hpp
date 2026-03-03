#ifndef MOVE_DATA_HPP
#define MOVE_DATA_HPP

#include <string>
#include "Type.hpp"


enum class MoveCategory
{
    Physical,
    Special,
    Status
};

struct MoveData
{
    int id;
    std::string name;
    Type type;
    int power;
    int accuracy;
    int pp;
    MoveCategory category;
};

#endif