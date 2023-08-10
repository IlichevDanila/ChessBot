#include <iostream>

#include "Declarations.hpp"
#include "Position.hpp"
#include "Piece.hpp"
#include "Move.hpp"
#include "Board.hpp"
#include "Searcher.hpp"

int main()
{
    std::cout << "Position: " << sizeof(Position) << " byte(s)" << std::endl;
    std::cout << "PieceBody: " << sizeof(PieceBody) << " byte(s)" << std::endl;
    std::cout << "Piece: " << sizeof(Piece) << " byte(s)" << std::endl;
    std::cout << "PieceSet: " << sizeof(PieceSet) << " byte(s)" << std::endl;
    std::cout << "Move: " << sizeof(Move) << " byte(s)" << std::endl;
    std::cout << "MoveSet: " << sizeof(MoveSet) << " byte(s)" << std::endl;
    std::cout << "Board: " << sizeof(Board) << " byte(s)" << std::endl;

    //Board board = Board::startingBoard();
    Board board = Board::fromFEN("2b1k3/pp2n2p/n1p1p1p1/4P3/2Q1N3/2P2r2/P1q2bPP/3RKB1R", 'w', "-", '-', 0, 2);
    std::cout << std::endl << board.getDislayString() << std::endl;

    std::string notation;

    std::cin >> notation;
    while (notation != "q")
    {
        if(notation == "moves")
        {
            MoveSet legalMoves = board.getLegalMoves();
            for(Move &mv: legalMoves)
            {
                std::cout << mv.ToNotation() << std::endl;
            }
        }
        else if(notation == "perft")
        {
            unsigned int depth;
            std::cin >> depth;
            std::cout << board.perft(depth) << std::endl;
        }
        else if(notation == "divide")
        {
            unsigned int depth;
            std::cin >> depth;
            board.divide(depth);
        }
        else if(notation == "play")
        {
            Searcher searcher;
            Move move = searcher.getBestMove(board, board.currentColor(), 3);
            board = board.doMove(move);
            std::cout << move.ToNotation() << std::endl;
            std::cout << std::endl << board.getDislayString() << std::endl;
        }
        else if(notation == "fen")
        {
            std::string pieces;
            char c;
            std::string castles;
            char es;
            int undoable_moves;
            int moves;
            std::cin >> pieces >> c >> castles >> es >> undoable_moves >> moves;
            board = Board::fromFEN(pieces, c, castles, es, undoable_moves, moves);
            std::cout << std::endl << board.getDislayString() << std::endl;
        }
        else
        {
            Move move = Move::FromNotation(notation, board);
            if(board.checkIfMovePseudolegal(move) && board.checkIfMoveLegal(move))
            {
                std::cout << "Legal move" << std::endl;
                board = board.doMove(move);
                std::cout << std::endl << board.getDislayString() << std::endl;
            }
            else
            {
                std::cout << "Illegal move" << std::endl;
            }
        }

        std::cin >> notation;
    }

    return 0;
}