#ifndef MOVE_HPP
#define MOVE_HPP

#include "Declarations.hpp"
#include "Position.hpp"

struct Move
{
    Color color;
    PiecePtr movingPiece;
    PiecePtr capturedPiece;
    PiecePtr promotionResult;
    Position from, to;
    bool longCastle, shortCastle;

    Move(
        Color color_,
        PiecePtr movingPiece_, 
        Position from_,
        Position to_,
        PiecePtr capturedPiece_ = nullptr,
        PiecePtr promotionResult_ = nullptr,
        bool longCastle_ = false,
        bool shortCastle_ = false
    );
};

#endif