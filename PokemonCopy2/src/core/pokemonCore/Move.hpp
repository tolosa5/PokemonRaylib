#ifndef MOVE_HPP
#define MOVE_HPP

#include <string>
#include "MoveData.hpp"

class Move
{
public:
    Move(const MoveData* moveData);
    virtual ~Move();
    
    const MoveData* data;
    int currentPP;
};

#endif