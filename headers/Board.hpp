#ifndef BOARD_HPP
#define BOARD_HPP

#include <cstdint>
#include <list>
#include <string>
#include <map>
#include <utility>

#include "Declarations.hpp"
#include "Piece.hpp"


class Board
{
private:
    Color playerColor = Color::White;
    PieceSet whitePieces;
    PieceSet blackPieces;
    Piece enPassPawn;

    static const char DisplayTypes[2][7];

public:
    Board();
    Board(const Board &rhs);
    Board(Board &&rhs);
    ~Board();

    Board &operator=(const Board &rhs);
    //Board &operator=(Board &&rhs);

    static Board startingBoard();

    inline Color currentColor() const { return playerColor; }
    inline Piece getEnPassPawn() const { return enPassPawn; }

    Piece *getPieceByPos(Position pos);
    Piece *getPieceByPos(Position pos, Color hint);
    const Piece *getPieceByPos(Position pos) const;
    const Piece *getPieceByPos(Position pos, Color hint) const;

    MoveSet getPseudolegalMoves() const;
    MoveSet getPseudolegalMoves(Color color) const;
    MoveSet getLegalMoves() const;
    MoveSet getLegalMoves(Color color) const;
    
    FuturesSet getFutures() const;

    bool checkIfMovePseudolegal(const Move &move) const;
    bool checkIfMoveLegal(const Move &move, Board *future = nullptr) const;

    bool ifCheck() const;
    bool ifMate() const;
    bool ifCheck(Color color) const;
    bool ifMate(Color color) const;

    std::uint64_t getAttackedMask(Color color) const;

    Board doMove(const Move &move) const;

    std::string getDislayString() const;
    std::string getFENString() const;

    unsigned long long perft(unsigned int depth = 1) const;
    void divide(unsigned int depth = 2) const;

    friend class Searcher;
};

#endif