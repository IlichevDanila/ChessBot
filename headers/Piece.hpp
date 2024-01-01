#ifndef PIECE_HPP
#define PIECE_HPP

#include "Declarations.hpp"

struct Piece
{
    unsigned char color : 1;
    unsigned char type : 3;

    Piece();
    Piece(char c);

    char getChar() const;
};

#endif