#include "Move.hpp"

#include "Position.hpp"

Move::Move(
        Color color_,
        PiecePtr movingPiece_, 
        Position from_,
        Position to_,
        PiecePtr capturedPiece_,
        PiecePtr promotionResult_,
        bool longCastle_,
        bool shortCastle_
    )
    : color(color_)
    , movingPiece(movingPiece_)
    , from(from_)
    , to(to_)
    , capturedPiece(capturedPiece_)
    , promotionResult(promotionResult_)
    , longCastle(longCastle_)
    , shortCastle(shortCastle_)
{

}