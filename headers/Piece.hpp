#ifndef PIECE_HPP
#define PIECE_HPP

#include <list>

#include "Declarations.hpp"
#include "Position.hpp"

class Piece
{
private:
    static int count;
    int id;

protected:
    Position pos;
    Color color;
    PieceType type;

public:
    Piece(Color color_, PieceType type_, Position pos_);
    ~Piece();

    Color getColor() const;
    PieceType getType() const;
    Position getPos() const;

    void setPos(Position pos_);

    std::list<Move> getMoves(const Board &) const;
};


#endif