#ifndef DECLARATIONS_HPP
#define DECLARATIONS_HPP

#include <bitset>
#include <list>

struct Piece
{
    unsigned char color : 1;
    unsigned char type : 3;
};

struct State
{
    Piece squares[64];
    unsigned char color : 1;
    unsigned char whiteCastlings : 2;
    unsigned char blackCastlings : 2;
    unsigned char epFile : 4;
};

using bitboard = std::bitset<64>;

struct Board
{
    State state;
    unsigned char fiftyMoveCounter : 6;
    //StatesHistory history;

    bitboard whiteAttack;
    bitboard whitePawns;
    bitboard whiteKnights;
    bitboard whiteBishops;
    bitboard whiteRooks;
    bitboard whiteQueens;
    bitboard whiteKing;

    bitboard blackAttack;
    bitboard blackPawns;
    bitboard blackKnights;
    bitboard blackBishops;
    bitboard blackRooks;
    bitboard blackQueens;
    bitboard blackKing;

    std::list<Piece> captured;

    std::uint64_t hash;
    int eval;
};

struct Move
{
    //std::uint8_t from, to;
    unsigned char from: 6;
    unsigned char to: 6;
    unsigned char flags: 4;
    unsigned char prevFiftyMoveCounter: 6;
    unsigned char prevWhiteCastlings : 2;
    unsigned char prevBlackCastlings : 2;
    unsigned char prevEpFile : 4;
};

struct BoardDiff
{
    bitboard whiteAttack;
    bitboard whitePawns;
    bitboard whiteKnights;
    bitboard whiteBishops;
    bitboard whiteRooks;
    bitboard whiteQueens;
    bitboard whiteKing;

    bitboard blackAttack;
    bitboard blackPawns;
    bitboard blackKnights;
    bitboard blackBishops;
    bitboard blackRooks;
    bitboard blackQueens;
    bitboard blackKing;

    std::uint64_t hash;
    int eval;
};

#endif