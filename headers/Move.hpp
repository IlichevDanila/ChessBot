#ifndef MOVE_HPP
#define MOVE_HPP

#include "Declarations.hpp"
#include "Piece.hpp"

class Move
{
public:
    enum CastleType : std::uint8_t {None = 0, Short = 1, Long = 2};

private:
    Color color;
    Position from, to;
    PieceBody promotion;
    CastleType castle;

    Move(Position from_, Position to_,
        Color color_, PieceBody promotion_,
        CastleType castle_)
        : from(from_), to(to_)
        , color(color_), promotion(promotion_)
        , castle(castle_)
    {}

public:
    Move() : color(Color::Black), from(), to(), castle(CastleType::None), promotion() {}
    ~Move();

    inline static Move SimpleMovement(Piece piece, Position dest)
    {
        return Move(
            piece.pos, dest,
            static_cast<Color>(piece.body.color),
            PieceBody(), CastleType::None
        );
    }

    inline static Move Promotion(Piece piece, Position dest, PieceType promType)
    {
        return Move(
            piece.pos, dest,
            static_cast<Color>(piece.body.color),
            PieceBody(piece.body.color, promType, 1), CastleType::None
        );
    }

    inline static Move ShortCastle(Color color)
    {
        return Move(
            Position(), Position(),
            color,
            PieceBody(), CastleType::Short
        );
    }

    inline static Move LongCastle(Color color)
    {
        return Move(
            Position(), Position(),
            color,
            PieceBody(), CastleType::Long
        );
    }

    friend Board;
};

#endif