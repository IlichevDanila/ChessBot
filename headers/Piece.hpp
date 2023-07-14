#ifndef PIECE_HPP
#define PIECE_HPP

#include <list>

#include "Declarations.hpp"
#include "Position.hpp"

class Piece
{
private:
    unsigned char color : 2;
    unsigned char type : 3;
    unsigned char moved : 1;
    Position pos;

public:
    Piece(Color color_, PieceType type_, Position pos_);

    static Piece EmptyPiece();

    Color getColor() const;
    PieceType getType() const;
    Position getPos() const;

    bool wasMoved() const;

    std::list<Move> getPseudolegalMoves() const;

    bool operator==(const Piece &rhs) const;
};

#endif