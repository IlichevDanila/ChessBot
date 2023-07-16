#ifndef BOARD_HPP
#define BOARD_HPP

#include <cstdint>
#include <list>
#include <string>

#include "Declarations.hpp"

//using PieceSet = std::list<Piece>;

class Board
{
private:
    Color playerColor = Color::White;
    PieceSet whitePieces;
    PieceSet blackPieces;
    Piece *enPassPawn = nullptr;

public:
    Board();
    Board(const Board &rhs);
    ~Board();

    static Board startingBoard();

    inline Color currentColor() const { return playerColor; }
    inline Piece *getEnPassPawn() { return enPassPawn; }
    inline const Piece *getEnPassPawn() const { return enPassPawn; }

    Piece *getPieceByPos(Position pos);
    Piece *getPieceByPos(Position pos, Color hint);
    const Piece *getPieceByPos(Position pos) const;
    const Piece *getPieceByPos(Position pos, Color hint) const;

    MoveSet getPseudolegalMoves() const;
    MoveSet getPseudolegalMoves(Color color) const;
    MoveSet getLegalMoves() const;
    MoveSet getLegalMoves(Color color) const;

    bool checkIfMovePseudolegal(const Move &move) const;
    bool checkIfMoveLegal(const Move &move) const;

    std::uint64_t getAttackedMask(Color color) const;

    Board doMove(const Move &move) const;

    std::string getDislayString() const;
};

#endif