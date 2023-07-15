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
    static Board startingBoard();

    inline Color currentColor() const { return playerColor; }
    inline Piece *getEnPassPawn() { return enPassPawn; }
    inline const Piece *getEnPassPawn() const { return enPassPawn; }

    Piece *getPieceByPos(Position pos);
    Piece *getPieceByPos(Position pos, Color hint);
    const Piece *getPieceByPos(Position pos) const;
    const Piece *getPieceByPos(Position pos, Color hint) const;

    MoveSet getPseudolegalMoves();
    MoveSet getPseudolegalMoves(Color color);
    MoveSet getLegalMoves();
    MoveSet getLegalMoves(Color color);

    bool checkIfMovePseudolegal(const Move &move) const;
    bool checkIfMoveLegal(const Move &move) const;

    Board doMove(const Move &move) const;

    std::string getDislayString() const;
};

#endif