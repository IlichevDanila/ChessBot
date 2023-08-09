#include <iostream>

#include "Searcher.hpp"

static constexpr double pawnPosValues[64] = 
    {
        0, 0, 0, 0, 0, 0, 0, 0,
        100, 100, 100, 100, 100, 100, 100, 100,
        70, 70, 70, 75, 75, 70, 70, 70,
        50, 50, 50, 55, 55, 50, 50, 50,
        30, 30, 33, 35, 35, 33, 30, 30,
        10, 10, 10, 20, 20, 10, 10, 10,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
    };

    static constexpr double knightPosValues[64] = 
    {
        -10, 0, 10, 10, 10, 10, 0, -10,
        0, 10, 20, 30, 30, 20, 10, 0,
        0, 20, 30, 40, 40, 30, 20, 0,
        0, 30, 40, 60, 60, 40, 30, 0,
        0, 30, 40, 60, 60, 40, 30, 0,
        0, 20, 30, 40, 40, 30, 20, 0,
        0, 10, 20, 30, 30, 20, 10, 0,
        -10, 0, 10, 10, 10, 10, 0, -10
    };

    static constexpr double bishopPosValues[64] = 
    {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 30, 20, 20, 30, 0, 0,
        0, 0, 20, 50, 50, 20, 0, 0,
        0, 0, 20, 50, 50, 20, 0, 0,
        0, 0, 30, 20, 20, 30, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
    };

    static constexpr double rookPosValues[64] = 
    {
        0, 10, 20, 20, 20, 20, 10, 0,
        10, 30, 30, 30, 30, 30, 30, 10,
        0, 20, 20, 20, 20, 20, 20, 0,
        0, 0, 20, 20, 20, 20, 0, 0,
        0, 0, 0, 20, 20, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        -20, -10, 0, 0, 0, 0, -10, -20
    };

    static constexpr double queenPosValues[64] = 
    {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 80, 80, 80, 80, 0, 0,
        0, 0, 80, 90, 90, 80, 0, 0,
        0, 0, 80, 90, 90, 80, 0, 0,
        0, 0, 80, 80, 80, 80, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
    };

    static constexpr double kingPosValues[64] = 
    {
        -40, -40, -30, -20, -20, -30, -40, -40
        -20, -10, -10, -10, -10, -10, -10, -20,
        0, 0, -20, -30, -30, -20, 0, 0,
        0, 0, -20, -50, -50, -20, 0, 0,
        0, 0, -10, -50, -50, -10, 0, 0,
        10, 0, 0, 0, 0, 0, 0, 10,
        20, 30, 10, 10, 10, 10, 30, 20,
        40, 50, 30, 20, 20, 30, 50, 40
    };

double Searcher::simple_eval(const Board &board, Color color) const
{
    double res = 0.0;

    //Draw
    if(board.ifPat())
    {
        return 0;
    }

    //Mate is the worst position
    if(board.ifMate())
    {
        return infNeg;
    }

    std::uint8_t posIdx;

    //Own pieces
    for(const Piece &p: color == Color::White? board.whitePieces : board.blackPieces)
    {
        int upsideDownRank = 7 - p.getPos().getRank();
        int posIdx = (upsideDownRank << 3) | p.getPos().getFile();
        switch(p.getType())
        {
        case PieceType::Pawn:
            res += pawnPosValues[posIdx];
            res += pawnValue;
            break;
        case PieceType::Knight:
            res += knightPosValues[posIdx];
            res += knightValue;
            break;
        case PieceType::Bishop:
            res += bishopPosValues[posIdx];
            res += bishopValue;
            break;
        case PieceType::Rook:
            res += rookPosValues[posIdx];
            res += rookValue;
            break;
        case PieceType::Queen:
            res += queenPosValues[posIdx];
            res += queenValue;
            break;
        default:
            res += kingPosValues[posIdx];
            break;
        }
    }

    //Enemy pieces
    for(const Piece &p: color == Color::White? board.blackPieces : board.whitePieces)
    {
        int upsideDownRank = 7 - p.getPos().getRank();
        int posIdx = (upsideDownRank << 3) | p.getPos().getFile();
        switch(p.getType())
        {
        case PieceType::Pawn:
            res -= pawnPosValues[posIdx];
            res -= pawnValue;
            break;
        case PieceType::Knight:
            res -= knightPosValues[posIdx];
            res -= knightValue;
            break;
        case PieceType::Bishop:
            res -= bishopPosValues[posIdx];
            res -= bishopValue;
            break;
        case PieceType::Rook:
            res -= rookPosValues[posIdx];
            res -= rookValue;
            break;
        case PieceType::Queen:
            res -= queenPosValues[posIdx];
            res -= queenValue;
            break;
        default:
            res -= kingPosValues[posIdx];
            break;
        }
    }

    //Own king is under check
    if(board.ifCheck())
    {
        res -= checkValue;
    }

    return res;
}

double Searcher::deep_eval(const Board &board, Color color, unsigned int depth, double alpha, double beta) const
{
    if(depth == 0)
    {
        return simple_eval(board, color);
    }

    double eval;
    for(auto &future: board.getFutures())
    {
        eval = -deep_eval(future.second, oppositeColor(color), depth - 1, -beta, -alpha);
        if(eval >= beta)
        {
            return beta;
        }

        alpha = std::max(alpha, eval);
    }

    return alpha;
}

Move Searcher::getBestMove(const Board &board, Color color, unsigned int depth, double alpha, double beta) const
{
    Move best;
    double eval;
    for(auto &future: board.getFutures())
    {
        eval = -deep_eval(future.second, oppositeColor(color), depth, -beta, -alpha);
        if(eval > alpha)
        {
            best = future.first;
        }
        alpha = std::max(alpha, eval);
    }
    return best;
}