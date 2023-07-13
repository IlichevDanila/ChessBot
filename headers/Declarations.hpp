#ifndef DECLARATIONS_HPP
#define DECLARATIONS_HPP

#include <memory>

class Position;

enum PieceType
{
    Pawn = 1,
    Knignt = 2,
    Bishop = 3,
    Rook = 4,
    Queen = 5,
    King = 6
};

enum Color
{
    Black = 1,
    White = 2,
    None = 0
};

class Piece;
class Pawn;
class Knight;
class Bishop;
class Rook;
class Queen;
class King;
using PiecePtr = std::shared_ptr<Piece>;

class Move;
using MovePtr = std::shared_ptr<Move>;

class Board;
using BoardPtr = std::shared_ptr<Board>;

#endif