#include "Move.hpp"

Move::Move(const MoveData* moveData)
    : data(moveData), currentPP(moveData ? moveData->pp : 0)
{
}

Move::~Move() = default;