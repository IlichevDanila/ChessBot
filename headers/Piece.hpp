#ifndef PIECE_HPP
#define PIECE_HPP

#include <cstdint>

#include "Declarations.hpp"
#include "Position.hpp"

struct PieceBody
{
    unsigned char moved : 1;
    unsigned char color : 2;
    unsigned char type : 3;

    PieceBody() : moved(0), color(0), type(0) {}

    PieceBody(unsigned char color_, unsigned char type_, unsigned char moved_ = 0)
        : color(color_ & 0x3), type(type_ & 0x7), moved(moved_ & 0x1)
    {}

    PieceBody(const PieceBody &rhs)
        : color(rhs.color), type(rhs.type), moved(rhs.moved)
    {}

    PieceBody(unsigned char ch)
        : type(ch & 0x7), color((ch >> 3) & 0x3), moved((ch >> 5) & 0x1)
    {}

    inline operator unsigned char() const { return (moved << 5) | (color << 3) | type; }
    std::uint8_t Hash() const { return (moved << 5) | (color << 3) | type; }
};

class Piece
{
private:
    PieceBody body;
    Position pos;

    MoveSet pawnMoves(const Board &board) const;
    MoveSet knightMoves(const Board &board) const;
    MoveSet bishopMoves(const Board &board) const;
    MoveSet rookMoves(const Board &board) const;
    MoveSet queenMoves(const Board &board) const;
    MoveSet kingMoves(const Board &board) const;

public:
    Piece() : body(), pos(0, 0) {}
    Piece(const Piece &rhs) : body(rhs.body), pos(rhs.pos) {}
    Piece(PieceBody body_, Position pos_) : body(body_), pos(pos_) {}
    Piece(Color color_, PieceType type_, Position pos_) : body(color_, type_, 0), pos(pos_) {}

    inline Piece &operator=(const Piece &rhs)
    {
        body = rhs.body;
        pos = rhs.pos;
        return *this;
    }

    inline std::uint16_t Hash() { return (pos.Hash() << 8) | body.Hash(); }

    inline bool operator==(const Piece &rhs) const { return body == rhs.body && pos == rhs.pos; }
    inline bool operator!=(const Piece &rhs) const { return body != rhs.body || pos != rhs.pos; }
    inline bool operator>(const Piece &rhs) const
    {
        return body > rhs.body || (body == rhs.body && pos > rhs.pos);
    }
    inline bool operator<(const Piece &rhs) const
    {
        return body < rhs.body || (body == rhs.body && pos < rhs.pos);
    }

    inline Color getColor() const { return static_cast<Color>(body.color); }
    inline PieceType getType() const { return static_cast<PieceType>(body.type); }
    inline Position getPos() const { return pos; }

    MoveSet getPseudolegalMoves(const Board &board) const;

    inline bool wasMoved() const { return body.moved == 1; }
    inline void setMoved() { body.moved = 1; }
    inline void unsetMoved() { body.moved = 0; }

    friend PieceSet;
};

class PieceSet
{
private:
    char size;
    Piece pieces[16];

public:
    inline Piece *begin() { return pieces; }
    inline Piece *end() { return &pieces[size]; }
    inline const Piece *begin() const { return pieces; }
    inline const Piece *end() const { return &pieces[size]; }

    void push_back(Piece newPiece);

    Piece *find(Piece piece);
    const Piece *find(Piece piece) const;
    Piece *find(Position pos);
    const Piece *find(Position pos) const;

    void erase(Piece *piece);
};

#endif