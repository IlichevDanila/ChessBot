#include <iostream>

#include "Declarations.hpp"

int main()
{
    std::cout << "Piece: " << sizeof(Piece) << std::endl;
    std::cout << "State: " << sizeof(State) << std::endl;
    std::cout << "Board: " << sizeof(Board) << std::endl;
    std::cout << "Move: " << sizeof(Move) << std::endl;
    std::cout << "BoardDiff: " << sizeof(BoardDiff) << std::endl;
    return 0;
}