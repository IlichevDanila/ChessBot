#ifndef MOVE_HPP
#define MOVE_HPP

#include "Declarations.hpp"

struct Move
{
    Pos from, to;
    unsigned char flags: 4;
    unsigned char prevFiftyMoveCounter: 6;
    unsigned char castlingRights : 4;
    unsigned char prevEpFile : 4;
};

#endif