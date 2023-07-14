#include <iostream>

#include "Declarations.hpp"
#include "Board.hpp"

int main()
{
    Board board;
    std::cout << board.getDisplayString() << std::endl;
    std::string command = "e2-e4";
    do
    {
        board.doMove(board.createMoveFromNotation(command));
        std::cout << std::endl << board.getDisplayString() << std::endl;
        std::cin >> command;
    } while (command != "");
    
    return 0;
}