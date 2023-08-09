#ifndef SEARCHER_HPP
#define SEARCHER_HPP

#include "Declarations.hpp"
#include "Board.hpp"
#include "Move.hpp"

class Searcher
{
private:
    static constexpr double pawnValue = 100.0;
    static constexpr double knightValue = 300.0;
    static constexpr double bishopValue = 300.0;
    static constexpr double rookValue = 500.0;
    static constexpr double queenValue = 900.0;

    static constexpr double checkValue = 200.0;

    static constexpr double infPos = 1e128;
    static constexpr double infNeg = -infPos;

    /*static constexpr double pawnPosValues[64] = 
    {
        0, 0, 0, 0, 0, 0, 0, 0,
        100, 100, 100, 100, 100, 100, 100, 100,
        70, 70, 70, 75, 75, 70, 70, 70,
        50, 50, 50, 55, 55, 50, 50, 50,
        30, 30, 33, 35, 35, 33, 30, 30,
        10, 10, 10, 20, 20, 10, 10, 10,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
    };

    static constexpr double knightPosValues[64] = 
    {
        -10, 0, 10, 10, 10, 10, 0, -10,
        0, 10, 20, 30, 30, 20, 10, 0,
        0, 20, 30, 40, 40, 30, 20, 0,
        0, 30, 40, 60, 60, 40, 30, 0,
        0, 30, 40, 60, 60, 40, 30, 0,
        0, 20, 30, 40, 40, 30, 20, 0,
        0, 10, 20, 30, 30, 20, 10, 0,
        -10, 0, 10, 10, 10, 10, 0, -10
    };

    static constexpr double bishopPosValues[64] = 
    {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 30, 20, 20, 30, 0, 0,
        0, 0, 20, 50, 50, 20, 0, 0,
        0, 0, 20, 50, 50, 20, 0, 0,
        0, 0, 30, 20, 20, 30, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
    };

    static constexpr double rookPosValues[64] = 
    {
        0, 10, 20, 20, 20, 20, 10, 0,
        10, 30, 30, 30, 30, 30, 30, 10,
        0, 20, 20, 20, 20, 20, 20, 0,
        0, 0, 20, 20, 20, 20, 0, 0,
        0, 0, 0, 20, 20, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        -20, -10, 0, 0, 0, 0, -10, -20
    };

    static constexpr double queenPosValues[64] = 
    {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 80, 80, 80, 80, 0, 0,
        0, 0, 80, 90, 90, 80, 0, 0,
        0, 0, 80, 90, 90, 80, 0, 0,
        0, 0, 80, 80, 80, 80, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
    };

    static constexpr double kingPosValues[64] = 
    {
        -40, -40, -30, -20, -20, -30, -40, -40
        -20, -10, -10, -10, -10, -10, -10, -20,
        0, 0, -20, -30, -30, -20, 0, 0,
        0, 0, -20, -50, -50, -20, 0, 0,
        0, 0, -10, -50, -50, -10, 0, 0,
        10, 0, 0, 0, 0, 0, 0, 10,
        20, 30, 10, 10, 10, 10, 30, 20,
        40, 50, 30, 20, 20, 30, 50, 40
    };*/

public:
    double simple_eval(const Board &board, Color color) const;
    double deep_eval(const Board &board, Color color, unsigned int depth = 1) const;
    Move getBestMove(const Board &board, Color color, unsigned int depth = 1) const;
};

#endif