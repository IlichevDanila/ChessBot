#include "Piece.hpp"
#include "Board.hpp"

Piece::Piece(Color color_, PieceType type_, Position pos_)
    : moves(0), color(color_), type(type_), pos(pos_)
{}

Piece::~Piece()
{}

Color Piece::getColor() const
{
    return color;
}

PieceType Piece::getType() const
{
    return type;
}

Position Piece::getPos() const
{
    return pos;
}

void Piece::setPos(Position pos_)
{
    pos = pos_;
    ++moves;
}

int Piece::getMoves() const
{
    return moves;
}

static std::list<Move> getBishopMoves(PiecePtr movingPiece, Board &board)
{
    std::list<Move> result;

    Color color = movingPiece->getColor();
    Position from = movingPiece->getPos();
    Position &pos = from;
    PiecePtr capturedPiece(nullptr);
    Position to;

    for(char i = 1; i < 8; ++i)
    {
        to = Position(pos.getFile() + i, pos.getRank() + i);
        capturedPiece = board.pieceInPlace(to);

        //Ally blocks the path
        if(!to.checkBounds() || (capturedPiece != nullptr && capturedPiece->getColor() == color))
        {
            break;
        }

        //Enemy blocks the path
        if(capturedPiece != nullptr)
        {
            result.push_back(Move(
                color, movingPiece, from, to,
                capturedPiece
            ));
            break;
        }
        //Nothing blocks the path
        else
        {
            result.push_back(Move(
                color, movingPiece, from, to
            ));
        }
    }

    for(char i = 1; i < 8; ++i)
    {
        to = Position(pos.getFile() + i, pos.getRank() - i);
        capturedPiece = board.pieceInPlace(to);

        //Ally blocks the path
        if(!to.checkBounds() || (capturedPiece != nullptr && capturedPiece->getColor() == color))
        {
            break;
        }

        //Enemy blocks the path
        if(capturedPiece != nullptr)
        {
            result.push_back(Move(
                color, movingPiece, from, to,
                capturedPiece
            ));
            break;
        }
        //Nothing blocks the path
        else
        {
            result.push_back(Move(
                color, movingPiece, from, to
            ));
        }
    }

    for(char i = 1; i < 8; ++i)
    {
        to = Position(pos.getFile() - i, pos.getRank() + i);
        capturedPiece = board.pieceInPlace(to);

        //Ally blocks the path
        if(!to.checkBounds() || (capturedPiece != nullptr && capturedPiece->getColor() == color))
        {
            break;
        }

        //Enemy blocks the path
        if(capturedPiece != nullptr)
        {
            result.push_back(Move(
                color, movingPiece, from, to,
                capturedPiece
            ));
            break;
        }
        //Nothing blocks the path
        else
        {
            result.push_back(Move(
                color, movingPiece, from, to
            ));
        }
    }

    for(char i = 1; i < 8; ++i)
    {
        to = Position(pos.getFile() - i, pos.getRank() - i);
        capturedPiece = board.pieceInPlace(to);

        //Ally blocks the path
        if(!to.checkBounds() || (capturedPiece != nullptr && capturedPiece->getColor() == color))
        {
            break;
        }

        //Enemy blocks the path
        if(capturedPiece != nullptr)
        {
            result.push_back(Move(
                color, movingPiece, from, to,
                capturedPiece
            ));
            break;
        }
        //Nothing blocks the path
        else
        {
            result.push_back(Move(
                color, movingPiece, from, to
            ));
        }
    }

    return result;
}

static std::list<Move> getRookMoves(PiecePtr movingPiece, Board &board)
{
    std::list<Move> result;

    Color color = movingPiece->getColor();
    Position from = movingPiece->getPos();
    Position &pos = from;
    PiecePtr capturedPiece(nullptr);
    Position to;

    for(char i = 1; i < 8; ++i)
    {
        to = Position(pos.getFile() + i, pos.getRank());
        capturedPiece = board.pieceInPlace(to);

        //Ally blocks the path
        if(!to.checkBounds() || (capturedPiece != nullptr && capturedPiece->getColor() == color))
        {
            break;
        }

        //Enemy blocks the path
        if(capturedPiece != nullptr)
        {
            result.push_back(Move(
                color, movingPiece, from, to,
                capturedPiece
            ));
            break;
        }
        //Nothing blocks the path
        else
        {
            result.push_back(Move(
                color, movingPiece, from, to
            ));
        }
    }

    for(char i = 1; i < 8; ++i)
    {
        to = Position(pos.getFile(), pos.getRank() + i);
        capturedPiece = board.pieceInPlace(to);

        //Ally blocks the path
        if(!to.checkBounds() || (capturedPiece != nullptr && capturedPiece->getColor() == color))
        {
            break;
        }

        //Enemy blocks the path
        if(capturedPiece != nullptr)
        {
            result.push_back(Move(
                color, movingPiece, from, to,
                capturedPiece
            ));
            break;
        }
        //Nothing blocks the path
        else
        {
            result.push_back(Move(
                color, movingPiece, from, to
            ));
        }
    }

    for(char i = 1; i < 8; ++i)
    {
        to = Position(pos.getFile() - i, pos.getRank());
        capturedPiece = board.pieceInPlace(to);

        //Ally blocks the path
        if(!to.checkBounds() || (capturedPiece != nullptr && capturedPiece->getColor() == color))
        {
            break;
        }

        //Enemy blocks the path
        if(capturedPiece != nullptr)
        {
            result.push_back(Move(
                color, movingPiece, from, to,
                capturedPiece
            ));
            break;
        }
        //Nothing blocks the path
        else
        {
            result.push_back(Move(
                color, movingPiece, from, to
            ));
        }
    }

    for(char i = 1; i < 8; ++i)
    {
        to = Position(pos.getFile(), pos.getRank() - i);
        capturedPiece = board.pieceInPlace(to);

        //Ally blocks the path
        if(!to.checkBounds() || (capturedPiece != nullptr && capturedPiece->getColor() == color))
        {
            break;
        }

        //Enemy blocks the path
        if(capturedPiece != nullptr)
        {
            result.push_back(Move(
                color, movingPiece, from, to,
                capturedPiece
            ));
            break;
        }
        //Nothing blocks the path
        else
        {
            result.push_back(Move(
                color, movingPiece, from, to
            ));
        }
    }

    return result;
}

std::list<Move> Piece::getPseudolegalMoves(Board &board)
{
    std::list<Move> result;

    Position from = pos;
    Position to;
    PiecePtr movingPiece(this);
    PiecePtr capturedPiece(nullptr);
    PiecePtr promotion(nullptr);
    bool shortCastle = false;
    bool longCastle = false;

    char pawnDirection = color == Color::White ? 1 : -1;
    char pawnPromotionRank = color == Color::White ? 7 : 0;

    std::list<Move> chunk;

    switch(type)
    {
    case PieceType::Pawn:
        //Simple move
        to = Position(pos.getFile(), pos.getRank() + pawnDirection);
        capturedPiece = board.pieceInPlace(to);
        if(to.checkBounds() && capturedPiece == nullptr)
        {
            //Promotion
            if(to.getRank() == pawnPromotionRank)
            {
                for(auto promType : {PieceType::Knight, PieceType::Bishop, PieceType::Rook, PieceType::Queen})
                {
                    promotion = std::make_shared<Piece>(color, promType, to);
                    result.push_back(Move(
                        color, movingPiece, from, to,
                        nullptr, promotion
                    ));
                }
            }
            else
            {
                result.push_back(Move(
                    color, movingPiece, from, to
                ));
            }

            //Double first move
            to = Position(pos.getFile(), pos.getRank() + 2 * pawnDirection);
            capturedPiece = board.pieceInPlace(to);
            if(moves == 0 && to.checkBounds() && capturedPiece == nullptr)
            {
                result.push_back(Move(
                    color, movingPiece, from, to
                ));
            }
        }

        //Simple capture or en-passant (or however it called idk)
        to = Position(pos.getFile() + 1, pos.getRank() + pawnDirection);
        capturedPiece = board.pieceInPlace(to);
        if(to.checkBounds())
        {
            //Capture
            if(capturedPiece != nullptr)
            {
                if(to.getRank() == pawnPromotionRank)
                {
                    for(auto promType : {PieceType::Knight, PieceType::Bishop, PieceType::Rook, PieceType::Queen})
                    {
                        promotion = std::make_shared<Piece>(color, promType, to);
                        result.push_back(Move(
                            color, movingPiece, from, to,
                            capturedPiece, promotion
                        ));
                    }
                }
                else
                {
                    result.push_back(Move(
                        color, movingPiece, from, to,
                        capturedPiece
                    ));
                }
            }
            //Maybe en-passant?
            else if(board.getPrevEnPass() != nullptr &&
                board.getPrevEnPass()->getPos() == Position(pos.getFile() + 1, pos.getRank()))
            {
                capturedPiece = board.getPrevEnPass();
                result.push_back(Move(
                    color, movingPiece, from, to,
                    capturedPiece
                ));
            }
        }

        to = Position(pos.getFile() - 1, pos.getRank() + pawnDirection);
        capturedPiece = board.pieceInPlace(to);
        if(to.checkBounds())
        {
            //Capture
            if(capturedPiece != nullptr)
            {
                if(to.getRank() == pawnPromotionRank)
                {
                    for(auto promType : {PieceType::Knight, PieceType::Bishop, PieceType::Rook, PieceType::Queen})
                    {
                        promotion = std::make_shared<Piece>(color, promType, to);
                        result.push_back(Move(
                            color, movingPiece, from, to,
                            capturedPiece, promotion
                        ));
                    }
                }
                else
                {
                    result.push_back(Move(
                        color, movingPiece, from, to,
                        capturedPiece
                    ));
                }
            }
            //Maybe en-passant?
            else if(board.getPrevEnPass() != nullptr &&
                board.getPrevEnPass()->getPos() == Position(pos.getFile() - 1, pos.getRank()))
            {
                capturedPiece = board.getPrevEnPass();
                result.push_back(Move(
                    color, movingPiece, from, to,
                    capturedPiece
                ));
            }
        }

        return result;
    case PieceType::Knight:
        for(auto iterPos : {
            Position(pos.getFile() + 1, pos.getRank() + 2),
            Position(pos.getFile() + 1, pos.getRank() - 2),
            Position(pos.getFile() - 1, pos.getRank() + 2),
            Position(pos.getFile() - 1, pos.getRank() - 2),
            Position(pos.getFile() + 2, pos.getRank() + 1),
            Position(pos.getFile() + 2, pos.getRank() - 1),
            Position(pos.getFile() - 2, pos.getRank() + 1),
            Position(pos.getFile() - 2, pos.getRank() - 1),
        })
        {
            to = iterPos;
            capturedPiece = board.pieceInPlace(to);
            if(to.checkBounds() && (capturedPiece == nullptr || capturedPiece->getColor() != color))
            {
                result.push_back(Move(
                    color, movingPiece, from, to,
                    capturedPiece
                ));
            }
        }
        
        return result;
    case PieceType::Bishop:
        return getBishopMoves(PiecePtr(this), board);
    case PieceType::Rook:
        return getRookMoves(PiecePtr(this), board);
    case PieceType::Queen:
        result = getBishopMoves(PiecePtr(this), board);
        chunk = getRookMoves(PiecePtr(this), board);
        result.insert(result.end(), chunk.begin(), chunk.end());
        return result;
    case PieceType::King:
        for(char dr = -1; dr <= 1; ++dr)
        {
            for(char df = -1; df <= 1; ++df)
            {
                if(dr == 0 && df == 0)
                {
                    continue;
                }

                to = Position(pos.getFile() + df, pos.getRank() + dr);
                capturedPiece = board.pieceInPlace(to);
                if(to.checkBounds() && (capturedPiece == nullptr || capturedPiece->color != color))
                {
                    result.push_back(Move(
                        color, movingPiece,
                        from, to, capturedPiece
                    ));
                }
            }
        }
        return result;
    default:
        return {};
    }
}