#ifndef MOVE_HPP
#define MOVE_HPP

#include "Declarations.hpp"
#include "Position.hpp"

struct PositionChange
{
    Position from, to;
};

struct Move
{
    unsigned char movedCount : 2;
    unsigned char deletedCount : 2;
    unsigned char firstMovesCount : 2;
    unsigned char promotionCount : 1;
    unsigned char enPassPawnChange : 1;

    PositionChange *moves;
    Piece *deletedPieces;
    Piece *piecesWithFirstMove;
    Piece *promotion;
    Piece *enPassPawn;

    Move();
    ~Move();
};


#endif