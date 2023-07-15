#include "Position.hpp"

bool Position::safeToAdd(char dfile, char drank) const
{
    return dfile + file >= 0 && dfile + file < 8 &&
           drank + rank >= 0 && drank + rank < 8;
}

bool Position::safeToAdd(Position dp) const
{
    return dp.file + file >= 0 && dp.file + file < 8 &&
           dp.rank + rank >= 0 && dp.rank + rank < 8;
}

Position Position::add(char dfile, char drank) const
{
    return Position(file + dfile, rank + drank);
}

Position Position::add(Position dp) const
{
    return Position(file + dp.file, rank + dp.rank);
}