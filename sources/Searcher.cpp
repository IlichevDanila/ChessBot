#include "Searcher.hpp"


double Searcher::simple_eval(const Board &board, Color color) const
{
    double res = 0.0;

    //Own pieces
    for(const Piece &p: color == Color::White? board.whitePieces : board.blackPieces)
    {
        switch(p.getType())
        {
        case PieceType::Pawn:
            res += pawnValue;
            break;
        case PieceType::Knight:
            res += knightValue;
            break;
        case PieceType::Bishop:
            res += bishopValue;
            break;
        case PieceType::Rook:
            res += rookValue;
            break;
        case PieceType::Queen:
            res += queenValue;
            break;
        default:
            break;
        }
    }

    //Enemy pieces
    for(const Piece &p: color == Color::White? board.blackPieces : board.whitePieces)
    {
        switch(p.getType())
        {
        case PieceType::Pawn:
            res -= pawnValue;
            break;
        case PieceType::Knight:
            res -= knightValue;
            break;
        case PieceType::Bishop:
            res -= bishopValue;
            break;
        case PieceType::Rook:
            res -= rookValue;
            break;
        case PieceType::Queen:
            res -= queenValue;
            break;
        default:
            break;
        }
    }

    //Own king is undr check
    if(board.ifCheck(color))
    {
        res -= checkValue;
    }

    //Enemy's king is under check
    if(board.ifCheck(oppositeColor(color)))
    {
        res += checkValue;
    }

    return res;
}

double Searcher::deep_eval(const Board &board, Color color, unsigned int depth) const
{
    if(depth == 0)
    {
        return simple_eval(board, color);
    }

    double bestEval = infNeg;
    double eval;
    for(auto &future: board.getFutures())
    {
        if((eval = -deep_eval(future.second, oppositeColor(color), depth - 1)) > bestEval)
        {
            bestEval = eval;
        }
    }

    return bestEval;
}

Move Searcher::getBestMove(const Board &board, Color color, unsigned int depth) const
{
    Move best;
    double bestEval = infNeg;
    double eval;
    for(auto &future: board.getFutures())
    {
        if((eval = -deep_eval(future.second, oppositeColor(color), depth)) > bestEval)
        {
            bestEval = eval;
            best = future.first;
        }
    }
    return best;
}