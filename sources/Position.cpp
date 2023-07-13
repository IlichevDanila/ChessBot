#include "Position.hpp"

Position::Position() : file(0), rank(0)
{}

Position::Position(const std::string &str) : file(str[0] - 'a'), rank(str[1] - '1')
{}

Position::Position(const Position &rhs) : file(rhs.file), rank(rhs.rank)
{}

Position::Position(char file_, char rank_) : file(file_), rank(rank_)
{}


bool Position::operator>(Position rhs) const
{
    if(file > rhs.file)
    {
        return true;
    }
    
    if(file < rhs.file)
    {
        return false;
    }

    return rank > rhs.rank;
}

bool Position::operator<(Position rhs) const
{
    if(file < rhs.file)
    {
        return true;
    }
    
    if(file > rhs.file)
    {
        return false;
    }

    return rank < rhs.rank;
}

Position &Position::operator=(Position rhs)
{
    file = rhs.file;
    rank = rhs.rank;
    return *this;
}

std::string Position::getString() const
{
    const static char *files = "abcdefgh";
    return files[file] + std::to_string(rank + 1);
}