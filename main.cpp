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

    Piece p1, p2('P'), p3('r'), p4('7');
    std::cout << p1.getChar() << std::endl;
    std::cout << p2.getChar() << std::endl;
    std::cout << p3.getChar() << std::endl;
    std::cout << p4.getChar() << std::endl;
    
    return 0;
}