#include <stdexcept>
#include <iostream>

#include "Position.hpp"
#include "Piece.hpp"
#include "Move.hpp"
#include "Board.hpp"

const char Board::DisplayTypes[2][7] = {
    {'.', 'p', 'n', 'b', 'r', 'q', 'k'},
    {'.', 'P', 'N', 'B', 'R', 'Q', 'K'}
};

Board::Board()
{}

Board::Board(const Board &rhs)
    : playerColor(rhs.playerColor)
    , whitePieces(rhs.whitePieces)
    , blackPieces(rhs.blackPieces)
    , enPassPawn(rhs.enPassPawn)
{
    
}

Board::Board(Board &&rhs)
    : playerColor(rhs.playerColor)
    , whitePieces(std::move(rhs.whitePieces))
    , blackPieces(std::move(rhs.blackPieces))
    , enPassPawn(rhs.enPassPawn)
{
    rhs.playerColor = Color::Black;
    rhs.enPassPawn = Piece();
}

Board::~Board()
{}

Board &Board::operator=(const Board &rhs)
{
    playerColor = rhs.playerColor;
    whitePieces = rhs.whitePieces;
    blackPieces = rhs.blackPieces;
    enPassPawn = rhs.enPassPawn;
    return *this;
}

/*Board &Board::operator=(Board &&rhs)
{
    playerColor = rhs.playerColor;
    whitePieces = std::move(rhs.whitePieces);
    blackPieces = std::move(rhs.blackPieces);
    enPassPawn = rhs.enPassPawn;
    rhs.playerColor = Color::Black;
    rhs.enPassPawn = Piece();
}*/

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
    result.whitePieces.push_back(Piece(Color::White, PieceType::Knight, Position(1, 0)));
    result.whitePieces.push_back(Piece(Color::White, PieceType::Bishop, Position(2, 0)));
    result.whitePieces.push_back(Piece(Color::White, PieceType::Queen, Position(3, 0)));
    result.whitePieces.push_back(Piece(Color::White, PieceType::King, Position(4, 0)));
    result.whitePieces.push_back(Piece(Color::White, PieceType::Bishop, Position(5, 0)));
    result.whitePieces.push_back(Piece(Color::White, PieceType::Knight, Position(6, 0)));
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
    result.blackPieces.push_back(Piece(Color::Black, PieceType::Knight, Position(1, 7)));
    result.blackPieces.push_back(Piece(Color::Black, PieceType::Bishop, Position(2, 7)));
    result.blackPieces.push_back(Piece(Color::Black, PieceType::Queen, Position(3, 7)));
    result.blackPieces.push_back(Piece(Color::Black, PieceType::King, Position(4, 7)));
    result.blackPieces.push_back(Piece(Color::Black, PieceType::Bishop, Position(5, 7)));
    result.blackPieces.push_back(Piece(Color::Black, PieceType::Knight, Position(6, 7)));
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
    MoveSet result;
    for(const Piece &p : color == Color::White ? whitePieces : blackPieces)
    {
        MoveSet chunk = p.getPseudolegalMoves(*this);
        result.insert(result.end(), chunk.begin(), chunk.end());
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

bool Board::checkIfMoveLegal(const Move &move, Board *ftr) const
{
    /*if(!checkIfMovePseudolegal(move))
    {
        return false;
    }*/

    Board future = doMove(move);
    if(ftr != nullptr)
    {
        *ftr = future;
    }

    return !future.ifCheck(playerColor);
}

std::uint64_t Board::getAttackedMask(Color color) const
{
    std::uint64_t res = 0;

    if(color == Color::White)
    {
        for(const Piece &p : whitePieces)
        {
            res |= p.getAttackedMask(*this);
        }
    }
    else
    {
        for(const Piece &p : blackPieces)
        {
            res |= p.getAttackedMask(*this);
        }
    }

    return res;
}

Board Board::doMove(const Move &move) const
{
    Board future(*this);

    //Short castle
    if(move.castle == Move::CastleType::Short)
    {
        if(playerColor == Color::White)
        {
            Piece *king = future.getPieceByPos(Position(4, 0));
            Piece *rook = future.getPieceByPos(Position(7, 0));
            king->pos = Position(6, 0);
            rook->pos = Position(5, 0);
            king->setMoved();
            rook->setMoved();
            future.playerColor = Color::Black;
        }
        else
        {
            Piece *king = future.getPieceByPos(Position(4, 7));
            Piece *rook = future.getPieceByPos(Position(7, 7));
            king->pos = Position(6, 7);
            rook->pos = Position(5, 7);
            king->setMoved();
            rook->setMoved();
            future.playerColor = Color::White;
        }
        future.enPassPawn = Piece();
        return future;
    }

    //Long castle
    if(move.castle == Move::CastleType::Long)
    {
        if(playerColor == Color::White)
        {
            Piece *king = future.getPieceByPos(Position(4, 0));
            Piece *rook = future.getPieceByPos(Position(0, 0));
            king->pos = Position(2, 0);
            rook->pos = Position(3, 0);
            king->setMoved();
            rook->setMoved();
            future.playerColor = Color::Black;
        }
        else
        {
            Piece *king = future.getPieceByPos(Position(4, 7));
            Piece *rook = future.getPieceByPos(Position(0, 7));
            king->pos = Position(2, 7);
            rook->pos = Position(3, 7);
            king->setMoved();
            rook->setMoved();
            future.playerColor = Color::White;
        }
        future.enPassPawn = Piece();
        return future;
    }

    //Move the piece
    Piece *movingPiece = future.getPieceByPos(move.from);
    Piece *target = future.getPieceByPos(move.to);
    movingPiece->pos = move.to;
    movingPiece->setMoved();

    //Capture the piece
    if(target != nullptr)
    {
        if(target->getColor() == Color::White)
        {
            future.whitePieces.erase(target);
        }
        else
        {
            future.blackPieces.erase(target);
        }
    }

    //En Passant
    if(move.enPass)
    {
        if(playerColor == Color::White)
        {
            future.blackPieces.erase(future.blackPieces.find(future.enPassPawn));
        }
        else
        {
            future.whitePieces.erase(future.whitePieces.find(future.enPassPawn));
        }
    }

    future.enPassPawn = Piece();
    if(movingPiece->body.type == PieceType::Pawn &&
        (move.to.getRank() - move.from.getRank() == 2 || move.to.getRank() - move.from.getRank() == -2)
    )
    {
        future.enPassPawn = *movingPiece;
    }

    //Promotion
    if(move.promotion != PieceBody())
    {
        movingPiece->body = move.promotion;
    }

    future.playerColor = future.playerColor == Color::White? Color::Black : Color::White;

    return future;
}

MoveSet Board::getLegalMoves() const
{
    MoveSet result, chunk;
    chunk = getPseudolegalMoves(playerColor);
    for(Move &mv: chunk)
    {
        if(checkIfMoveLegal(mv))
        {
            result.push_back(mv);
        }
    }
    return result;
}

FuturesSet Board::getFutures() const
{
    FuturesSet result;
    //MoveSet moves;
    Board brd;
    for(Move &mv: getPseudolegalMoves(playerColor))
    {
        if(checkIfMoveLegal(mv, &brd))
        {
            result.insert(make_future(mv, brd));
        }
    }
    return result;
}

unsigned long long Board::perft(unsigned int depth) const
{
    if(depth == 0)
    {
        return 1;
    }

    if(depth == 1)
    {
        return getLegalMoves().size();
    }

    unsigned long long res = 0;

    FuturesSet futures = getFutures();
    for(auto &future : futures)
    {
        res += future.second.perft(depth - 1);
    }

    return res;
}

void Board::divide(unsigned int depth) const
{
    if(depth == 0)
    {
        return;
    }

    if(depth == 1)
    {
        for(auto &mv: getLegalMoves())
        {
            std::cout << mv.ToNotation() << ": 1" << std::endl;
        }
        std::cout << std::endl << "Nodes searched: " << getLegalMoves().size() << std::endl;
        return;
    }

    FuturesSet futures = getFutures();
    unsigned long long perfts = 0;
    unsigned long long perftRes = 0;
    for(auto &future : futures)
    {
        perftRes = future.second.perft(depth - 1);
        perfts += perftRes;
        std::cout << future.first.ToNotation() << ": " << perftRes << std::endl;
    }

    std::cout << std::endl << "Nodes searched: " << perfts << std::endl;
}

std::string Board::getFENString() const
{
    std::string res = "";
    for(int rank = 7; rank >= 0; --rank)
    {
        int space = 0;
        for(int file = 0; file < 9; ++file)
        {
            const Piece *p = getPieceByPos(Position(file, rank));
            if(p == nullptr)
            {
                ++space;
                continue;
            }

            if(space != 0)
            {
                res += std::to_string(space);
            }
            res += DisplayTypes[p->getColor()][p->getType()];
        }
        if(rank > 0)
        {
            res += "/";
        }
    }

    res += ' ';
    res += playerColor == Color::Black? 'b' : 'w';
    res += " - ";
    if(enPassPawn != Piece())
    {
        res += std::to_string(enPassPawn.getPos().getFile() + 'a');
        res += playerColor == Color::White? '6' : '3';
    }
    else
    {
        res += '-';
    }
    res += "0 0";

    return res;
}

bool Board::ifCheck() const
{
    const Piece *king = (playerColor == Color::White? whitePieces : blackPieces).getKing();
    std::uint64_t attack = getAttackedMask(playerColor == Color::White? Color::Black : Color::White);
    return (attack & king->getPos().boardMask()) != 0;
}

bool Board::ifCheck(Color color) const
{
    const Piece *king = (color == Color::White? whitePieces : blackPieces).getKing();
    std::uint64_t attack = getAttackedMask(color == Color::White? Color::Black : Color::White);
    return (attack & king->getPos().boardMask()) != 0;
}

bool Board::ifMate() const
{
    return getLegalMoves().size() == 0 && ifCheck();
}

bool Board::ifPat() const
{
    return getLegalMoves().size() == 0 && !ifCheck();
}

Board Board::fromFEN(const std::string &pieces,
                        char c,
                        const std::string &castles,
                        char es,
                        int undoable_moves,
                        int moves)
{
    Board brd;

    brd.playerColor = c == 'w'? Color::White : Color::Black;

    int file = 0;
    int rank = 7;
    Piece newPiece;

    for(auto ch: pieces)
    {
        switch(ch)
        {
        case 'p':
            newPiece = Piece(Color::Black, PieceType::Pawn, Position(file, rank));
            if(rank != 6)
            {
                newPiece.setMoved();
            }
            brd.blackPieces.push_back(newPiece);
            break;
        case 'P':
            newPiece = Piece(Color::White, PieceType::Pawn, Position(file, rank));
            if(rank != 1)
            {
                newPiece.setMoved();
            }
            brd.whitePieces.push_back(newPiece);
            break;
        case 'n':
            brd.blackPieces.push_back(Piece(Color::Black, PieceType::Knight, Position(file, rank)));
            break;
        case 'N':
            brd.whitePieces.push_back(Piece(Color::White, PieceType::Knight, Position(file, rank)));
            break;
        case 'b':
            brd.blackPieces.push_back(Piece(Color::Black, PieceType::Bishop, Position(file, rank)));
            break;
        case 'B':
            brd.whitePieces.push_back(Piece(Color::White, PieceType::Bishop, Position(file, rank)));
            break;
        case 'r':
            newPiece = Piece(Color::Black, PieceType::Rook, Position(file, rank));
            newPiece.setMoved();
            brd.blackPieces.push_back(newPiece);
            break;
        case 'R':
            newPiece = Piece(Color::White, PieceType::Rook, Position(file, rank));
            newPiece.setMoved();
            brd.whitePieces.push_back(newPiece);
            break;
        case 'q':
            brd.blackPieces.push_back(Piece(Color::Black, PieceType::Queen, Position(file, rank)));
            break;
        case 'Q':
            brd.whitePieces.push_back(Piece(Color::White, PieceType::Queen, Position(file, rank)));
            break;
        case 'k':
            brd.blackPieces.push_back(Piece(Color::Black, PieceType::King, Position(file, rank)));
            break;
        case 'K':
            brd.whitePieces.push_back(Piece(Color::White, PieceType::King, Position(file, rank)));
            break;
        case '/':
            --rank;
            file = -1;
            break;
        default:
            file += ch - '1';
        }
        ++file;
    }

    brd.whitePieces.getKing()->setMoved();
    brd.blackPieces.getKing()->setMoved();

    for(auto ch: castles)
    {
        switch(ch)
        {
        case 'k':
            brd.blackPieces.getKing()->unsetMoved();
            brd.getPieceByPos(Position(7, 7))->unsetMoved();
            break;
        case 'q':
            brd.blackPieces.getKing()->unsetMoved();
            brd.getPieceByPos(Position(0, 7))->unsetMoved();
            break;
        case 'K':
            brd.whitePieces.getKing()->unsetMoved();
            brd.getPieceByPos(Position(7, 0))->unsetMoved();
            break;
        case 'Q':
            brd.whitePieces.getKing()->unsetMoved();
            brd.getPieceByPos(Position(0, 0))->unsetMoved();
            break;
        }
    }

    if(es != '-')
    {
        brd.enPassPawn = *brd.getPieceByPos(brd.playerColor == Color::White? Position(es - '1', 5) : Position(es - '1', 4));
    }

    return brd;
}