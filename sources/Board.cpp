#include <stdexcept>

#include "Position.hpp"
#include "Piece.hpp"
#include "Move.hpp"
#include "Board.hpp"

Board Board::startingBoard()
{
    Board result;

    result.whitePieces.push_back(Piece(Color::White, PieceType::Pawn, Position(0, 1)));
    result.whitePieces.push_back(Piece(Color::White, PieceType::Pawn, Position(1, 1)));
    result.whitePieces.push_back(Piece(Color::White, PieceType::Pawn, Position(2, 1)));
    result.whitePieces.push_back(Piece(Color::White, PieceType::Pawn, Position(3, 1)));
    result.whitePieces.push_back(Piece(Color::White, PieceType::Pawn, Position(4, 1)));
    result.whitePieces.push_back(Piece(Color::White, PieceType::Pawn, Position(5, 1)));
    result.whitePieces.push_back(Piece(Color::White, PieceType::Pawn, Position(6, 1)));
    result.whitePieces.push_back(Piece(Color::White, PieceType::Pawn, Position(7, 1)));

    result.whitePieces.push_back(Piece(Color::White, PieceType::Rook, Position(0, 0)));
    result.whitePieces.push_back(Piece(Color::White, PieceType::Bishop, Position(1, 0)));
    result.whitePieces.push_back(Piece(Color::White, PieceType::Knight, Position(2, 0)));
    result.whitePieces.push_back(Piece(Color::White, PieceType::Queen, Position(3, 0)));
    result.whitePieces.push_back(Piece(Color::White, PieceType::King, Position(4, 0)));
    result.whitePieces.push_back(Piece(Color::White, PieceType::Knight, Position(5, 0)));
    result.whitePieces.push_back(Piece(Color::White, PieceType::Bishop, Position(6, 0)));
    result.whitePieces.push_back(Piece(Color::White, PieceType::Rook, Position(7, 0)));


    result.blackPieces.push_back(Piece(Color::Black, PieceType::Pawn, Position(0, 6)));
    result.blackPieces.push_back(Piece(Color::Black, PieceType::Pawn, Position(1, 6)));
    result.blackPieces.push_back(Piece(Color::Black, PieceType::Pawn, Position(2, 6)));
    result.blackPieces.push_back(Piece(Color::Black, PieceType::Pawn, Position(3, 6)));
    result.blackPieces.push_back(Piece(Color::Black, PieceType::Pawn, Position(4, 6)));
    result.blackPieces.push_back(Piece(Color::Black, PieceType::Pawn, Position(5, 6)));
    result.blackPieces.push_back(Piece(Color::Black, PieceType::Pawn, Position(6, 6)));
    result.blackPieces.push_back(Piece(Color::Black, PieceType::Pawn, Position(7, 6)));

    result.blackPieces.push_back(Piece(Color::Black, PieceType::Rook, Position(0, 7)));
    result.blackPieces.push_back(Piece(Color::Black, PieceType::Bishop, Position(1, 7)));
    result.blackPieces.push_back(Piece(Color::Black, PieceType::Knight, Position(2, 7)));
    result.blackPieces.push_back(Piece(Color::Black, PieceType::Queen, Position(3, 7)));
    result.blackPieces.push_back(Piece(Color::Black, PieceType::King, Position(4, 7)));
    result.blackPieces.push_back(Piece(Color::Black, PieceType::Knight, Position(5, 7)));
    result.blackPieces.push_back(Piece(Color::Black, PieceType::Bishop, Position(6, 7)));
    result.blackPieces.push_back(Piece(Color::Black, PieceType::Rook, Position(7, 7)));

    return result;
}



Piece *Board::getPieceByPos(Position pos)
{
    Piece *result;
    if(playerColor == Color::White)
    {
        result = whitePieces.find(pos);
        if(result == nullptr)
        {
            result = blackPieces.find(pos);
        }
        return result;
    }
    else
    {
        result = blackPieces.find(pos);
        if(result == nullptr)
        {
            result = whitePieces.find(pos);
        }
        return result;
    }
}

Piece *Board::getPieceByPos(Position pos, Color hint)
{
    Piece *result;
    if(hint == Color::White)
    {
        result = whitePieces.find(pos);
        if(result == nullptr)
        {
            result = blackPieces.find(pos);
        }
        return result;
    }
    else
    {
        result = blackPieces.find(pos);
        if(result == nullptr)
        {
            result = whitePieces.find(pos);
        }
        return result;
    }
}

const Piece *Board::getPieceByPos(Position pos) const
{
    const Piece *result;
    if(playerColor == Color::White)
    {
        result = whitePieces.find(pos);
        if(result == nullptr)
        {
            result = blackPieces.find(pos);
        }
        return result;
    }
    else
    {
        result = blackPieces.find(pos);
        if(result == nullptr)
        {
            result = whitePieces.find(pos);
        }
        return result;
    }
}

const Piece *Board::getPieceByPos(Position pos, Color hint) const
{
    const Piece *result;
    if(hint == Color::White)
    {
        result = whitePieces.find(pos);
        if(result == nullptr)
        {
            result = blackPieces.find(pos);
        }
        return result;
    }
    else
    {
        result = blackPieces.find(pos);
        if(result == nullptr)
        {
            result = whitePieces.find(pos);
        }
        return result;
    }
}


std::string Board::getDislayString() const
{
    static char DisplayTypes[2][7] = {
        {'.', 'P', 'N', 'B', 'R', 'Q', 'K'},
        {'.', 'p', 'n', 'b', 'r', 'q', 'k'}
    };
    std::string res;
    for(int rank = 7; rank >= 0; --rank)
    {
        res += std::to_string(rank + 1) + " ";
        for(int file = 0; file < 8; ++file)
        {
            const Piece *p = getPieceByPos(Position(file, rank));
            if(p == nullptr)
            {
                res += '.';
            }
            else
            {
                res += DisplayTypes[p->getColor()][p->getType()];
            }
        }
        res += '\n';
    }
    res += "  abcdefgh";
    return res;
}

MoveSet Board::getPseudolegalMoves() const
{
    MoveSet result, chunk;
    for(const Piece &p : whitePieces)
    {
        chunk = p.getPseudolegalMoves(*this);
        result.insert(result.end(), chunk.begin(), chunk.end());
    }
    for(const Piece &p : blackPieces)
    {
        chunk = p.getPseudolegalMoves(*this);
        result.insert(result.end(), chunk.begin(), chunk.end());
    }
    return result;
}

MoveSet Board::getPseudolegalMoves(Color color) const
{
    MoveSet result, chunk;
    if(color == Color::White)
    {
        for(const Piece &p : whitePieces)
        {
            chunk = p.getPseudolegalMoves(*this);
            result.insert(result.end(), chunk.begin(), chunk.end());
        }    
    }
    else
    {
        for(const Piece &p : blackPieces)
        {
            chunk = p.getPseudolegalMoves(*this);
            result.insert(result.end(), chunk.begin(), chunk.end());
        }
    }
    
    return result;
}

bool Board::checkIfMovePseudolegal(const Move &move) const
{
    if(playerColor != move.color)
    {
        return false;
    }

    const Piece *piece = getPieceByPos(move.from);
    if(piece == nullptr)
    {
        return false;
    }

    bool found = false;
    for(Move &mv : piece->getPseudolegalMoves(*this))
    {
        if(mv == move)
        {
            found = true;
            break;
        }
    }

    return found;
}

bool Board::checkIfMoveLegal(const Move &move) const
{
    /*if(!checkIfMovePseudolegal(move))
    {
        return false;
    }*/

    Board future = doMove(move);

    Piece *king = nullptr;
    if(move.color == Color::White)
    {
        for(Piece &p : future.whitePieces)
        {
            if(p.getType() == PieceType::King)
            {
                king = &p;
                break;
            }
        }
    }
    else
    {
        for(Piece &p : future.blackPieces)
        {
            if(p.getType() == PieceType::King)
            {
                king = &p;
                break;
            }
        }
    }

    if(king == nullptr)
    {
        throw std::runtime_error("King does not exist. Why?");
    }

    if((future.getAttackedMask(future.playerColor) & king->getPos().boardMask()) != 0)
    {
        return false;
    }

    return true;
}