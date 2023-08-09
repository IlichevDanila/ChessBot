#include <stdexcept>

#include "Move.hpp"
#include "Board.hpp"

Move Move::FromNotation(const std::string &notation, const Board &board)
{
    /*if(notation == "O-O")
    {
        return ShortCastle(board.currentColor());
    }
    if(notation == "O-O-O")
    {
        return LongCastle(board.currentColor());
    }*/

    const Piece *piece = board.getPieceByPos(Position(notation.substr(0, 2)));
    Position dest(notation.substr(2, 2));
    if(piece == nullptr)
    {
        throw std::runtime_error("No piece on position");
    }

    //Maybe it is a castle?
    if(piece->getType() == PieceType::King)
    {
        if(notation == "e1c1")
        {
            return LongCastle(Color::White);
        }
        else if(notation == "e8c8")
        {  
            return LongCastle(Color::Black);
        }
        else if(notation == "e1g1")
        {
            return ShortCastle(Color::White);
        }
        else if(notation == "e8g8")
        {  
            return ShortCastle(Color::Black);
        }
    }

    if(notation.size() == 5)
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

    if(board.getEnPassPawn() != Piece() &&
        (board.getEnPassPawn().getPos() == piece->getPos().add(-1, 0) || board.getEnPassPawn().getPos() == piece->getPos().add(1, 0)) &&
        board.getEnPassPawn().getColor() != piece->getColor())
    {
        return Move::EnPassant(*piece, dest);
    }

    return SimpleMovement(*piece, dest);
}

Move::~Move()
{}

std::string Move::ToNotation() const
{
    if(castle == CastleType::Long)
    {
        if(color == Color::Black)
        {
            return "e8c8";
        }
        else
        {
            return "e1c1";
        }
    }
    if(castle == CastleType::Short)
    {
        if(color == Color::Black)
        {
            return "e8g8";
        }
        else
        {
            return "e1g1";
        }
    }
    std::string res = from.to_string() + to.to_string();
    if(promotion != PieceBody())
    {
        static const char promTypeChars[] = {'.', 'p', 'n', 'b', 'r', 'q', 'k'};
        res += promTypeChars[promotion.type];
    }
    return res;
}