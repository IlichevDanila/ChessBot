#ifndef BOARD_HPP
#define BOARD_HPP

#include <list>
#include <string>

#include "Declarations.hpp"
#include "Move.hpp"

class Board
{
private:
    Color playerColor;

    PiecePtr prevEnPass;

    std::list<PiecePtr> whitePieces;
    std::list<PiecePtr> blackPieces;

    std::list<PiecePtr> capturedWhites;
    std::list<PiecePtr> capturedBlacks;

public:
    Board();

    PiecePtr pieceInPlace(Position pos);

    PiecePtr getPrevEnPass() const;

    Move createMoveFromNotation(const std::string &notation);
    bool checkIfMovePseudolegal(const Move &move);
    bool checkIfMoveLegal(const Move &move);

    std::list<Move> getPseudolegalMoves();
    std::list<Move> getLegalMoves();

    void doMove(const Move &move);
    void undoMove(const Move &move);

    std::string getDisplayString();
};


#endif