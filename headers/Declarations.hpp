#ifndef DECLARATIONS_HPP
#define DECLARATIONS_HPP

#include <cstdint>
#include <list>

class Position;

enum PieceType : std::uint8_t
{
    Pawn = 1,
    Knight = 2,
    Bishop = 3,
    Rook = 4,
    Queen = 5,
    King = 6,
    None = 0
};

enum Color : std::uint8_t
{
    Black = 0,
    White = 1
};

class Piece;
class PieceSet;

class Move;
//class MoveSet;
using MoveSet = std::list<Move>;

class Board;

#endif