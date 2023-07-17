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
    const Piece *enPass;

    Move(Position from_, Position to_,
        Color color_, PieceBody promotion_,
        CastleType castle_, const Piece *enPass_ = nullptr)
        : from(from_), to(to_)
        , color(color_), promotion(promotion_)
        , castle(castle_), enPass(enPass_)
    {}

public:
    inline std::uint32_t Hash() const
    {
        return (from.Hash() << 24) |
                (to.Hash() << 16) |
                (promotion << 8) |
                (castle << 3) |
                color;
    }

    Move()
        : color(Color::Black), from(), to()
        , castle(CastleType::None), promotion(), enPass(nullptr)
    {}

    ~Move();

    inline bool operator==(const Move &rhs)
    {
        return Hash() == rhs.Hash();
    }

    inline bool operator!=(const Move &rhs)
    {
        return Hash() == rhs.Hash();
    }

    static Move FromNotation(const std::string &notation, const Board &board);

    std::string ToNotation() const;

    inline static Move FromHash(std::uint32_t hash)
    {
        return Move(
            Position(hash >> 24), Position((hash >> 16) & 0xff),
            static_cast<Color>(hash & 0x3),
            PieceBody((hash >> 8) & 0xff),
            static_cast<CastleType>((hash >> 3) & 0x7)
        );
    }

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

    inline static Move EnPassant(Piece piece, Position dest, const Piece *enPassPawn)
    {
        return Move(
            piece.pos, dest,
            static_cast<Color>(piece.body.color),
            PieceBody(), CastleType::None, enPassPawn
        );
    }

    friend Board;
};

#endif