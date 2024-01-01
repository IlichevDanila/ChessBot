#ifndef BOARD_HPP
#define BOARD_HPP

#include "Declarations.hpp"
#include "State.hpp"

struct Board
{
    State state;
    unsigned char fiftyMoveCounter : 6;

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

    PieceList captured;

    Hash hash;
    int eval;

    Board(const std::string fen);

    std::string getString() const;

    void doMove(const Move &move);
    void undoMove(const Move &move);

    void recalcBitboards();
    void recalcEval();
    void recalcHash();

private:
    void doPawnMove(const Move &move);
    void doRookMove(const Move &move);
    void doKingMove(const Move &move);
    void doNormalMove(const Move &move);

    void undoPawnMove(const Move &move);
    void undoRookMove(const Move &move);
    void undoKingMove(const Move &move);
    void undoNormalMove(const Move &move);
};

#endif