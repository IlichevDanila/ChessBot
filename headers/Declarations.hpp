#ifndef DECLARATIONS_HPP
#define DECLARATIONS_HPP

#include <cstdint>
#include <list>
#include <map>
#include <utility>

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

inline Color oppositeColor(Color color)
{
    return color == Color::White? Color::Black : Color::White;
}

class Piece;
class PieceSet;

class Move;
//class MoveSet;
using MoveSet = std::list<Move>;

class Board;

using Future = std::pair<Move, Board>;
#define make_future(x, y) std::make_pair(x, y)
using FuturesSet = std::list<Future>;

class Searcher;

#endif