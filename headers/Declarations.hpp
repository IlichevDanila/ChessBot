#ifndef DECLARATIONS_HPP
#define DECLARATIONS_HPP

#include <memory>

class Position;

enum PieceType
{
    Pawn = 1,
    Knight = 2,
    Bishop = 3,
    Rook = 4,
    Queen = 5,
    King = 6,
    None = 0
};

enum Color
{
    Black = 0,
    White = 1
};

class Piece;
using PiecePtr = std::shared_ptr<Piece>;

class Move;
using MovePtr = std::shared_ptr<Move>;

class Board;
using BoardPtr = std::shared_ptr<Board>;

#endif