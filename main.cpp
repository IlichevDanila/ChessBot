#include <iostream>

#include "Declarations.hpp"
#include "Position.hpp"
#include "Piece.hpp"
#include "Move.hpp"
#include "Board.hpp"

int main()
{
    std::cout << "Position: " << sizeof(Position) << " byte(s)" << std::endl;
    std::cout << "PieceBody: " << sizeof(PieceBody) << " byte(s)" << std::endl;
    std::cout << "Piece: " << sizeof(Piece) << " byte(s)" << std::endl;
    std::cout << "PieceSet: " << sizeof(PieceSet) << " byte(s)" << std::endl;
    std::cout << "Move: " << sizeof(Move) << " byte(s)" << std::endl;
    std::cout << "MoveSet: " << sizeof(MoveSet) << " byte(s)" << std::endl;
    std::cout << "Board: " << sizeof(Board) << " byte(s)" << std::endl;

    Board board = Board::startingBoard();
    std::cout << std::endl << std::endl << board.getDislayString() << std::endl;

    return 0;
}