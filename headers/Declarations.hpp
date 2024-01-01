#ifndef DECLARATIONS_HPP
#define DECLARATIONS_HPP

#include <cstdint>
#include <list>

enum Color
{
    Black = 0,
    White = 1
};

enum PieceType
{
    None = 0,
    Pawn, Knight, Bishop, Rook, Queen, King
};

struct Piece;

enum class File
{
    File_A = 0, File_B, File_C, File_D, File_E, File_F, File_G, File_H,
    None = 15
};

enum class Rank
{
    Rank_1 = 0, Rank_2, Rank_3, Rank_4, Rank_5, Rank_6, Rank_7, Rank_8
};


constexpr int SquareCount = 64;
enum class Square
{
    A1 = 0, B1, C1, D1, E1, F1, G1, H1,
    A2, B2, C2, D2, E2, F2, G2, H2,
    A3, B3, C3, D3, E3, F3, G3, H3,
    A4, B4, C4, D4, E4, F4, G4, H4,
    A5, B5, C5, D5, E5, F5, G5, H5,
    A6, B6, C6, D6, E6, F6, G6, H6,
    A7, B7, C7, D7, E7, F7, G7, H7,
    A8, B8, C8, D8, E8, F8, G8, H8,
    None
};

enum class Direction
{
    Up = 12,
    Down = -12,
    Right = 1,
    Left = -1,
    UpRight = Up + Right,
    UpLeft = Up + Left,
    DownRight = Down + Right,
    DownLeft = Down + Left
};

enum class CastlingRights {
    None,
    WhiteOO,
    WhiteOOO = WhiteOO << 1,
    BlackOO  = WhiteOO << 2,
    BlackOOO = WhiteOO << 3,

    KingSide      = WhiteOO | BlackOO,
    QueenSide     = WhiteOOO | BlackOOO,
    WhiteCastling = WhiteOO | WhiteOOO,
    BlackCastling = BlackOO | BlackOOO,
    AnyCastling   = WhiteCastling | BlackCastling
};

struct State;

using bitboard = std::uint64_t;
using Hash = std::uint64_t;
using PieceList = std::list<Piece>;

struct Board;

using Pos = std::uint8_t;

enum class MoveFlag
{
    Quiet = 0,
    DoublePawnPush = 1,
    KingCastle = 2,
    QueenCastle = 3,
    Capture = 4,
    EpCapture = 5,
    KnightProm = 8,
    BishopProm = 9,
    RookProm = 10,
    QueenProm = 11,
    KnightPromCapt = 12,
    BishopPromCapt = 13,
    RookPromCapt = 14,
    QueenPromCapt = 15,
};

struct Move;

#endif