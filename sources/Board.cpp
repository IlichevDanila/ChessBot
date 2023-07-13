#include <exception>

#include "Position.hpp"
#include "Piece.hpp"
#include "Board.hpp"

PiecePtr Board::pieceInPlace(Position pos)
{
    for(auto ptr: whitePieces)
    {
        if(ptr->getPos() == pos)
        {
            return ptr;
        }
    }

    for(auto ptr: blackPieces)
    {
        if(ptr->getPos() == pos)
        {
            return ptr;
        }
    }

    return std::shared_ptr<Piece>(nullptr);
}

Board::Board() : playerColor(Color::White), prevEnPass(nullptr)
{
    whitePieces.push_back(std::make_shared<Piece>(Color::White, PieceType::Pawn, Position(0, 1)));
    whitePieces.push_back(std::make_shared<Piece>(Color::White, PieceType::Pawn, Position(1, 1)));
    whitePieces.push_back(std::make_shared<Piece>(Color::White, PieceType::Pawn, Position(2, 1)));
    whitePieces.push_back(std::make_shared<Piece>(Color::White, PieceType::Pawn, Position(3, 1)));
    whitePieces.push_back(std::make_shared<Piece>(Color::White, PieceType::Pawn, Position(4, 1)));
    whitePieces.push_back(std::make_shared<Piece>(Color::White, PieceType::Pawn, Position(5, 1)));
    whitePieces.push_back(std::make_shared<Piece>(Color::White, PieceType::Pawn, Position(6, 1)));
    whitePieces.push_back(std::make_shared<Piece>(Color::White, PieceType::Pawn, Position(7, 1)));

    whitePieces.push_back(std::make_shared<Piece>(Color::White, PieceType::Rook, Position(0, 0)));
    whitePieces.push_back(std::make_shared<Piece>(Color::White, PieceType::Bishop, Position(1, 0)));
    whitePieces.push_back(std::make_shared<Piece>(Color::White, PieceType::Knight, Position(2, 0)));
    whitePieces.push_back(std::make_shared<Piece>(Color::White, PieceType::Queen, Position(3, 0)));
    whitePieces.push_back(std::make_shared<Piece>(Color::White, PieceType::King, Position(4, 0)));
    whitePieces.push_back(std::make_shared<Piece>(Color::White, PieceType::Knight, Position(5, 0)));
    whitePieces.push_back(std::make_shared<Piece>(Color::White, PieceType::Bishop, Position(6, 0)));
    whitePieces.push_back(std::make_shared<Piece>(Color::White, PieceType::Rook, Position(7, 0)));



    blackPieces.push_back(std::make_shared<Piece>(Color::Black, PieceType::Pawn, Position(0, 6)));
    blackPieces.push_back(std::make_shared<Piece>(Color::Black, PieceType::Pawn, Position(1, 6)));
    blackPieces.push_back(std::make_shared<Piece>(Color::Black, PieceType::Pawn, Position(2, 6)));
    blackPieces.push_back(std::make_shared<Piece>(Color::Black, PieceType::Pawn, Position(3, 6)));
    blackPieces.push_back(std::make_shared<Piece>(Color::Black, PieceType::Pawn, Position(4, 6)));
    blackPieces.push_back(std::make_shared<Piece>(Color::Black, PieceType::Pawn, Position(5, 6)));
    blackPieces.push_back(std::make_shared<Piece>(Color::Black, PieceType::Pawn, Position(6, 6)));
    blackPieces.push_back(std::make_shared<Piece>(Color::Black, PieceType::Pawn, Position(7, 6)));

    blackPieces.push_back(std::make_shared<Piece>(Color::Black, PieceType::Rook, Position(0, 7)));
    blackPieces.push_back(std::make_shared<Piece>(Color::Black, PieceType::Bishop, Position(1, 7)));
    blackPieces.push_back(std::make_shared<Piece>(Color::Black, PieceType::Knight, Position(2, 7)));
    blackPieces.push_back(std::make_shared<Piece>(Color::Black, PieceType::King, Position(3, 7)));
    blackPieces.push_back(std::make_shared<Piece>(Color::Black, PieceType::Queen, Position(4, 7)));
    blackPieces.push_back(std::make_shared<Piece>(Color::Black, PieceType::Knight, Position(5, 7)));
    blackPieces.push_back(std::make_shared<Piece>(Color::Black, PieceType::Bishop, Position(6, 7)));
    blackPieces.push_back(std::make_shared<Piece>(Color::Black, PieceType::Rook, Position(7, 7)));
}


Move Board::createMoveFromNotation(const std::string &notation)
{
    PiecePtr movingPiece = nullptr;
    PiecePtr capturedPiece = nullptr;
    PiecePtr promotion = nullptr;
    Position from, to;
    bool shortCastle = false;
    bool longCastle = false;

    //Castles
    if(notation == "O-O" || notation == "O-O-O")
    {
        PiecePtr rookPiece;

        if(notation == "O-O")
        {
            shortCastle = true;

            if(playerColor == Color::White)
            {
                movingPiece = pieceInPlace(Position(4, 0));
                rookPiece = pieceInPlace(Position(0, 0));
            }
            else
            {
                movingPiece = pieceInPlace(Position(5, 7));
                movingPiece = pieceInPlace(Position(7, 7));
            }
        }
        else
        {
            longCastle = true;

            if(playerColor == Color::White)
            {
                movingPiece = pieceInPlace(Position(4, 0));
                rookPiece = pieceInPlace(Position(7, 0));
            }
            else
            {
                movingPiece = pieceInPlace(Position(5, 7));
                movingPiece = pieceInPlace(Position(0, 7));
            }
        }

        if(
            movingPiece == nullptr ||
            movingPiece->getType() != PieceType::King ||
            movingPiece->getMoves() != 0 ||
            rookPiece == nullptr ||
            rookPiece->getType() != PieceType::Rook ||
            rookPiece->getMoves() != 0
        )
        {
            throw std::runtime_error("Invalid castle");
        }
    }
    //Promotion
    else if(notation.size() == 6)
    {
        from = Position(notation.substr(0, 2));
        to = Position(notation.substr(3, 2));
        movingPiece = pieceInPlace(from);

        if(movingPiece == nullptr || movingPiece->getType() != PieceType::Pawn)
        {
            throw std::runtime_error("Invalid promotion");
        }

        switch(notation[5])
        {
        case 'n':
        case 'N':
            promotion = std::make_shared<Piece>(playerColor, PieceType::Knight, to);
            break;
        case 'b':
        case 'B':
            promotion = std::make_shared<Piece>(playerColor, PieceType::Bishop, to);
            break;
        case 'r':
        case 'R':
            promotion = std::make_shared<Piece>(playerColor, PieceType::Rook, to);
            break;
        case 'q':
        case 'Q':
            promotion = std::make_shared<Piece>(playerColor, PieceType::Queen, to);
            break;
        default:
            throw std::runtime_error("Invalid promotion");
        }
    }
    //Simple move
    else
    {
        from = Position(notation.substr(0, 2));
        to = Position(notation.substr(3, 2));
        movingPiece = pieceInPlace(from);
        capturedPiece = pieceInPlace(to);
    }

    return Move(playerColor, movingPiece,
        from, to,
        capturedPiece, promotion,
        longCastle, shortCastle);
}

bool Board::checkIfMovePseudolegal(const Move &move)
{
    if(move.longCastle)
    {
        PiecePtr rook, king;
        if(move.color == Color::White)
        {
            rook = pieceInPlace(Position(0, 0));
            king = pieceInPlace(Position(4, 0));

            return rook != nullptr &&
                   rook->getType() == PieceType::Rook &&
                   rook->getMoves() == 0 &&
                   pieceInPlace(Position(1, 0)) == nullptr &&
                   pieceInPlace(Position(2, 0)) == nullptr &&
                   pieceInPlace(Position(3, 0)) == nullptr &&
                   king != nullptr &&
                   king->getType() == PieceType::King &&
                   king->getMoves() == 0;
        }
        else
        {
            rook = pieceInPlace(Position(7, 7));
            king = pieceInPlace(Position(3, 7));

            return rook != nullptr &&
                   rook->getType() == PieceType::Rook &&
                   rook->getMoves() == 0 &&
                   pieceInPlace(Position(4, 7)) == nullptr &&
                   pieceInPlace(Position(5, 7)) == nullptr &&
                   pieceInPlace(Position(6, 7)) == nullptr &&
                   king != nullptr &&
                   king->getType() == PieceType::King &&
                   king->getMoves() == 0;
        }
    }
    else if(move.shortCastle)
    {
        PiecePtr rook, king;
        if(move.color == Color::White)
        {
            rook = pieceInPlace(Position(7, 0));
            king = pieceInPlace(Position(4, 0));

            return rook != nullptr &&
                   rook->getType() == PieceType::Rook &&
                   rook->getMoves() == 0 &&
                   pieceInPlace(Position(5, 0)) == nullptr &&
                   pieceInPlace(Position(6, 0)) == nullptr &&
                   king != nullptr &&
                   king->getType() == PieceType::King &&
                   king->getMoves() == 0;
        }
        else
        {
            rook = pieceInPlace(Position(0, 7));
            king = pieceInPlace(Position(3, 7));

            return rook != nullptr &&
                   rook->getType() == PieceType::Rook &&
                   rook->getMoves() == 0 &&
                   pieceInPlace(Position(1, 7)) == nullptr &&
                   pieceInPlace(Position(2, 7)) == nullptr &&
                   king != nullptr &&
                   king->getType() == PieceType::King &&
                   king->getMoves() == 0;
        }
    }
    else if(move.promotionResult != nullptr)
    {
        if(move.movingPiece->getType() != PieceType::Pawn)
        {
            return false;
        }
    }
    
    //Promotion or simple

    std::list<Move> pseudolegalMoves = move.movingPiece->getPseudolegalMoves(*this);
    for(auto &possibleMove : pseudolegalMoves)
    {
        if(possibleMove.to == move.to)
        {
            return true;
        }
    }

    return false;
}

bool Board::checkIfMoveLegal(const Move &move)
{
    bool result = true;
    doMove(move);
    for(auto &nextMove : getPseudolegalMoves())
    {
        if(nextMove.capturedPiece != nullptr && nextMove.capturedPiece->getType() == PieceType::King)
        {
            result = false;
            break;
        }
    }
    undoMove(move);
    return result;
}


std::list<Move> Board::getPseudolegalMoves()
{
    std::list<Move> result, chunk;
    if(playerColor == Color::White)
    {
        for(auto &piece : whitePieces)
        {
            chunk = piece->getPseudolegalMoves(*this);
            result.insert(result.end(), chunk.begin(), chunk.end());
        }
        return result;
    }
    else
    {
        for(auto &piece : blackPieces)
        {
            chunk = piece->getPseudolegalMoves(*this);
            result.insert(result.end(), chunk.begin(), chunk.end());
        }
        return result;
    }
}

std::list<Move> Board::getLegalMoves()
{
    std::list<Move> result;
    for(auto &move : getPseudolegalMoves())
    {
        if(checkIfMoveLegal(move))
        {
            result.push_back(move);
        }
    }
    return result;
}

std::string Board::getDisplayString()
{
    std::string res = "";
    for(int rank = 7; rank >= 0; --rank)
    {
        res += std::to_string(rank + 1) + ' ';
        for(int file = 0; file < 8; ++file)
        {
            PiecePtr piece = pieceInPlace(Position(file, rank));
            if(piece == nullptr)
            {
                res += '.';
            }
            else
            {
                static const char *blackDispl = "pnbrqk";
                static const char *whiteDispl = "PNBRQK";
                if(piece->getColor() == Color::White)
                {
                    res += whiteDispl[piece->getType() - 1];
                }
                else
                {
                    res += blackDispl[piece->getType() - 1];
                }
            }
        }
        res += '\n';
    }
    res += "  abcdefgh";
    return res;
}

PiecePtr Board::getPrevEnPass() const
{
    return prevEnPass;
}