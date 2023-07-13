#ifndef POSITION_HPP
#define POSITION_HPP

#include <string>

class Position
{
private:
    char file, rank;

public:
    Position();
    Position(const std::string &str);
    Position(const Position &rhs);
    Position(char file_, char rank_);

    inline char getFile() const { return file; }
    inline char getRank() const { return rank; }

    inline bool checkBounds() const { return file >= 0 && file < 8 && rank >= 0 && rank < 8; }

    inline bool operator==(Position rhs) const { return file == rhs.file && rank == rhs.rank; }
    bool operator>(Position rhs) const;
    bool operator<(Position rhs) const;

    Position &operator=(Position rhs);

    std::string getString() const;
};


#endif