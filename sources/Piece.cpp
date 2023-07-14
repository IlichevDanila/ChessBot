#include "Piece.hpp"

Piece::Piece(Color color_, PieceType type_, Position pos_)
    : color(color_)
    , type(type_)
    , pos(pos_)
    , moved(0)
{}

Piece Piece::EmptyPiece()
{
    return Piece(Color::Black, PieceType::None, Position(0));
}

Color Piece::getColor() const
{
    return static_cast<Color>(color);
}

PieceType Piece::getType() const
{
    return static_cast<PieceType>(type);
}

Position Piece::getPos() const
{
    return pos;
}

bool Piece::wasMoved() const
{
    return static_cast<bool>(moved);
}

bool Piece::operator==(const Piece &rhs) const
{
    return color == rhs.color && type == rhs.type && pos == rhs.pos && moved == rhs.moved;
}

/*std::list<Move> Piece::getPseudolegalMoves() const
{
    return {};
}*/