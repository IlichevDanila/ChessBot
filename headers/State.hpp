#ifndef STATE_HPP
#define STATE_HPP

#include <string>

#include "Declarations.hpp"
#include "Piece.hpp"

struct State
{
    Piece squares[SquareCount];
    unsigned char color : 1;
    unsigned char whiteCastlings : 2;
    unsigned char blackCastlings : 2;
    unsigned char epFile : 4;

    State(const std::string &fen);

    std::string getString() const;
};

#endif