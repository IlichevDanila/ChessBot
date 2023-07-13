#ifndef BOARD_HPP
#define BOARD_HPP

#include <list>
#include <string>

#include "Move.hpp"

class Board
{
public:
    Board();
    
    std::list<Move> getPseudolegalMoves();
    std::list<Move> getLegalMoves();

    std::string getDisplayString() const;
};


#endif