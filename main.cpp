#include <iostream>

#include "Declarations.hpp"
#include "Piece.hpp"
#include "State.hpp"
#include "Board.hpp"
#include "Move.hpp"

int main()
{
    std::cout << "Piece: " << sizeof(Piece) << std::endl;
    std::cout << "State: " << sizeof(State) << std::endl;
    std::cout << "Board: " << sizeof(Board) << std::endl;
    std::cout << "Move: " << sizeof(Move) << std::endl;
    
    return 0;
}