#include "Piece.hpp"

Piece::Piece(): color(0), type(0) {}

Piece::Piece(char ch)
{
    switch(ch)
    {
    case 'p':
        color = Color::Black;
        type = PieceType::Pawn;
        break;
    case 'P':
        color = Color::White;
        type = PieceType::Pawn;
        break;
    case 'n':
        color = Color::Black;
        type = PieceType::Knight;
        break;
    case 'N':
        color = Color::White;
        type = PieceType::Knight;
        break;
    case 'b':
        color = Color::Black;
        type = PieceType::Bishop;
        break;
    case 'B':
        color = Color::White;
        type = PieceType::Bishop;
        break;
    case 'r':
        color = Color::Black;
        type = PieceType::Rook;
        break;
    case 'R':
        color = Color::White;
        type = PieceType::Rook;
        break;
    case 'q':
        color = Color::Black;
        type = PieceType::Queen;
        break;
    case 'Q':
        color = Color::White;
        type = PieceType::Queen;
        break;
    case 'k':
        color = Color::Black;
        type = PieceType::King;
        break;
    case 'K':
        color = Color::White;
        type = PieceType::King;
        break;
    default:
        color = 0;
        type = 0;
    }
}

char Piece::getChar() const
{
    static const char syms[] = ".pnbrqk..PNBRQK";
    return syms[(color << 3) | type];
}