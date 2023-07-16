#include "Piece.hpp"
#include "Move.hpp"
#include "Board.hpp"

Piece *PieceSet::find(Piece piece)
{
    if(size == 0)
        return nullptr;

    //TODO: binary search
    for(int i = 0; i < size; ++i)
    {
        if(pieces[i] == piece)
        {
            return &pieces[i];
        }
    }

    return nullptr;
}

const Piece *PieceSet::find(Piece piece) const
{
    if(size == 0)
        return nullptr;

    //TODO: binary search
    for(int i = 0; i < size; ++i)
    {
        if(pieces[i] == piece)
        {
            return &pieces[i];
        }
    }

    return nullptr;
}

Piece *PieceSet::find(Position pos)
{
    if(size == 0)
        return nullptr;

    //TODO: binary search
    for(int i = 0; i < size; ++i)
    {
        if(pieces[i].pos == pos)
        {
            return &pieces[i];
        }
    }

    return nullptr;
}

const Piece *PieceSet::find(Position pos) const
{
    if(size == 0)
        return nullptr;

    //TODO: binary search
    for(int i = 0; i < size; ++i)
    {
        if(pieces[i].pos == pos)
        {
            return &pieces[i];
        }
    }

    return nullptr;
}

void PieceSet::push_back(Piece piece)
{
    //TODO: Do i need check?
    if(find(piece.pos) != nullptr)
        return;

    if(size == 16)
        return;

    //TODO: sorted insertion
    pieces[size] = piece;
    ++size;
}

void PieceSet::erase(Piece *piece)
{
    //TODO: do i need check?
    if(piece < pieces || piece >= (pieces + size))
        return;

    //TODO: sorted erase
    *piece = *(pieces + (size - 1));
    --size;
}

MoveSet Piece::pawnMoves(const Board &board) const
{
    MoveSet result;

    char promotionRank = (body.color == Color::Black)? 7 : 0;
    char direction = (body.color == Color::Black)? 7 : 0;

    //Forward movement
    Position dest = pos.add(0, direction);
    const Piece *target = board.getPieceByPos(dest);
    if(target == nullptr)
    {
        if(dest.getRank() == promotionRank)
        {
            for(PieceType promType : {
                PieceType::Knight,
                PieceType::Bishop,
                PieceType::Rook,
                PieceType::Queen
            })
            {
                result.push_back(Move::Promotion(*this, dest, promType));
            }
        }
        else
        {
            result.push_back(Move::SimpleMovement(*this, dest));
        }

        if(!wasMoved())
        {
            dest = dest.add(0, direction);
            target = board.getPieceByPos(dest);
            if(target == nullptr)
            {
                result.push_back(Move::SimpleMovement(*this, dest));
            }
        }
    }

    //Capture
    dest = pos.add(1, direction);
    target = board.getPieceByPos(dest);
    const Piece *enPass = board.getEnPassPawn();
    if(target != nullptr && target->getColor() != body.color)
    {
        if(dest.getRank() == promotionRank)
        {
            for(PieceType promType : {
                PieceType::Knight,
                PieceType::Bishop,
                PieceType::Rook,
                PieceType::Queen
            })
            {
                result.push_back(Move::Promotion(*this, dest, promType));
            }
        }
        else
        {
            result.push_back(Move::SimpleMovement(*this, dest));
        }
    }
    //En passant (or however it called idk)
    else if(enPass != nullptr && enPass->getPos() == pos.add(1, 0))
    {
        result.push_back(Move::EnPassant(*this, dest, enPass));
    }

    dest = pos.add(-1, direction);
    target = board.getPieceByPos(dest);
    if(target != nullptr && target->getColor() != body.color)
    {
        if(dest.getRank() == promotionRank)
        {
            for(PieceType promType : {
                PieceType::Knight,
                PieceType::Bishop,
                PieceType::Rook,
                PieceType::Queen
            })
            {
                result.push_back(Move::Promotion(*this, dest, promType));
            }
        }
        else
        {
            result.push_back(Move::SimpleMovement(*this, dest));
        }
    }
    //En passant (or however it called idk)
    else if(enPass != nullptr && enPass->getPos() == pos.add(-1, 0))
    {
        result.push_back(Move::EnPassant(*this, dest, enPass));
    }

    return result;
}

MoveSet Piece::knightMoves(const Board &board) const
{
    MoveSet result;

    for(Position dp : {
        Position(1, 2),
        Position(1, -2),
        Position(-1, 2),
        Position(-1, -2),
        Position(2, 1),
        Position(2, -1),
        Position(-2, 1),
        Position(-2, -1)
    })
    {
        if(pos.safeToAdd(dp))
        {
            Position dest = pos.add(dp);
            const Piece *target = board.getPieceByPos(dest);
            if(target == nullptr || target->getColor() != body.color)
            {
                result.push_back(Move::SimpleMovement(*this, pos.add(dp)));
            }
        }
    }

    return result;
}

MoveSet Piece::bishopMoves(const Board &board) const
{
    MoveSet result;

    for(Position direction : {
        Position(1, 1),
        Position(1, -1),
        Position(-1, 1),
        Position(-1, -1)
    })
    {
        Position dest = pos;
        while(dest.safeToAdd(direction))
        {
            dest = dest.add(direction);
            const Piece *target = board.getPieceByPos(dest);
            if(target != nullptr && target->getColor() == body.color)
            {
                break;
            }
            else if(target != nullptr)
            {
                result.push_back(Move::SimpleMovement(*this, dest));
                break;
            }
            else
            {
                result.push_back(Move::SimpleMovement(*this, dest));
            }
        }
    }

    return result;
}

MoveSet Piece::rookMoves(const Board &board) const
{
    MoveSet result;

    for(Position direction : {
        Position(1, 0),
        Position(-1, 0),
        Position(0, 1),
        Position(0, -1)
    })
    {
        Position dest = pos;
        while(dest.safeToAdd(direction))
        {
            dest = dest.add(direction);
            const Piece *target = board.getPieceByPos(dest);
            if(target != nullptr && target->getColor() == body.color)
            {
                break;
            }
            else if(target != nullptr)
            {
                result.push_back(Move::SimpleMovement(*this, dest));
                break;
            }
            else
            {
                result.push_back(Move::SimpleMovement(*this, dest));
            }
        }
    }

    return result;
}

MoveSet Piece::queenMoves(const Board &board) const
{
    MoveSet result;

    for(Position direction : {
        Position(1, 1),
        Position(1, -1),
        Position(-1, 1),
        Position(-1, -1),
        Position(1, 0),
        Position(-1, 0),
        Position(0, 1),
        Position(0, -1)
    })
    {
        Position dest = pos;
        while(dest.safeToAdd(direction))
        {
            dest = dest.add(direction);
            const Piece *target = board.getPieceByPos(dest);
            if(target != nullptr && target->getColor() == body.color)
            {
                break;
            }
            else if(target != nullptr)
            {
                result.push_back(Move::SimpleMovement(*this, dest));
                break;
            }
            else
            {
                result.push_back(Move::SimpleMovement(*this, dest));
            }
        }
    }

    return result;
}

MoveSet Piece::kingMoves(const Board &board) const
{
    MoveSet result;

    for(Position dp : {
        Position(-1, -1),
        Position(-1, 0),
        Position(-1, 1),
        Position(0, -1),
        Position(0, 1),
        Position(1, -1),
        Position(1, 0),
        Position(1, 1)
    })
    {
        if(pos.safeToAdd(dp))
        {
            Position dest = pos.add(dp);
            const Piece *target = board.getPieceByPos(dest);
            if(target == nullptr || target->getColor() != body.color)
            {
                result.push_back(Move::SimpleMovement(*this, dest));
            }
        }
    }

    //Castles
    //TODO: check if mediate positions under attack
    if(wasMoved())
    {
        return result;
    }

    if(body.color == Color::White)
    {
        const Piece *rook = board.getPieceByPos(Position(0, 0));
        if(board.getPieceByPos(Position(1, 0)) == nullptr &&
            board.getPieceByPos(Position(2, 0)) == nullptr &&
            board.getPieceByPos(Position(3, 0)) == nullptr &&
            rook != nullptr &&
            rook->getType() == PieceType::Rook &&
            !rook->wasMoved())
        {
            result.push_back(Move::LongCastle(static_cast<Color>(body.color)));
        }

        rook = board.getPieceByPos(Position(7, 0));
        if(board.getPieceByPos(Position(6, 0)) == nullptr &&
            board.getPieceByPos(Position(5, 0)) == nullptr &&
            rook != nullptr &&
            rook->getType() == PieceType::Rook &&
            !rook->wasMoved())
        {
            result.push_back(Move::ShortCastle(static_cast<Color>(body.color)));
        }
    }
    else
    {
        const Piece *rook = board.getPieceByPos(Position(0, 7));
        if(board.getPieceByPos(Position(1, 7)) == nullptr &&
            board.getPieceByPos(Position(2, 7)) == nullptr &&
            board.getPieceByPos(Position(3, 7)) == nullptr &&
            rook != nullptr &&
            rook->getType() == PieceType::Rook &&
            !rook->wasMoved())
        {
            result.push_back(Move::LongCastle(static_cast<Color>(body.color)));
        }

        rook = board.getPieceByPos(Position(7, 7));
        if(board.getPieceByPos(Position(6, 7)) == nullptr &&
            board.getPieceByPos(Position(5, 7)) == nullptr &&
            rook != nullptr &&
            rook->getType() == PieceType::Rook &&
            !rook->wasMoved())
        {
            result.push_back(Move::ShortCastle(static_cast<Color>(body.color)));
        }
    }

    return result;
}

MoveSet Piece::getPseudolegalMoves(const Board &board) const
{
    switch(body.type)
    {
    case PieceType::Pawn:
        return pawnMoves(board);
    case PieceType::Knight:
        return knightMoves(board);
    case PieceType::Bishop:
        return bishopMoves(board);
    case PieceType::Rook:
        return rookMoves(board);
    case PieceType::Queen:
        return queenMoves(board);
    case PieceType::King:
        return kingMoves(board);
    default:
        return MoveSet();
    }
}