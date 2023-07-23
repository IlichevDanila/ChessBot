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

public:
    double simple_eval(const Board &board, Color color) const;
    double deep_eval(const Board &board, Color color, unsigned int depth = 1) const;
    Move getBestMove(const Board &board, Color color, unsigned int depth = 1) const;
};

#endif