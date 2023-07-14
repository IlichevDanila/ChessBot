#include "Position.hpp"

Position::Position(unsigned char ch)
    : file(ch & 0x7)
    , rank((ch >> 3) & 0x7)
{}

Position::Position(unsigned char file_, unsigned char rank_)
    : file(file_ & 0x7)
    , rank(rank_ & 0x7)
{}

Position::Position(const Position &rhs)
    : file(rhs.file)
    , rank(rhs.rank)
{}

Position::operator unsigned char() const
{
    return (rank << 3) | file;
}

unsigned char Position::getFile() const
{
    return file;
}

unsigned char Position::getRank() const
{
    return rank;
}

bool Position::safeToAdd(char dfile, char drank) const
{
    return dfile + file >= 0 && dfile + file < 8 &&
           drank + rank >= 0 && drank + rank < 8;
}

Position Position::add(char dfile, char drank) const
{
    return Position(file + dfile, rank + drank);
}

bool Position::operator==(const Position &rhs) const
{
    return file == rhs.file && rank == rhs.rank;
}