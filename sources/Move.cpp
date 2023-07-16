#include <stdexcept>

#include "Move.hpp"
#include "Board.hpp"

Move Move::FromNotation(const std::string &notation, const Board &board)
{
    if(notation == "O-O")
    {
        return ShortCastle(board.currentColor());
    }
    if(notation == "O-O-O")
    {
        return LongCastle(board.currentColor());
    }

    const Piece *piece = board.getPieceByPos(Position(notation.substr(0, 2)));
    Position dest(notation.substr(3, 2));
    if(piece == nullptr)
    {
        throw std::runtime_error("No piece on position");
    }

    if(notation.size() == 6)
    {
        PieceType promType;
        switch(notation[5])
        {
        case 'n':
        case 'N':
            promType = PieceType::Knight;
            break;
        case 'b':
        case 'B':
            promType = PieceType::Bishop;
            break;
        case 'r':
        case 'R':
            promType = PieceType::Rook;
            break;
        case 'q':
        case 'Q':
            promType = PieceType::Queen;
            break;
        default:
            throw std::runtime_error("Invalid promotion");
        }

        return Promotion(*piece, dest, promType);
    }

    return SimpleMovement(*piece, dest);
}

Move::~Move()
{}