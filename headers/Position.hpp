#ifndef POSITION_HPP
#define POSITION_HPP

#include <string>

class Position
{
private:
    unsigned char file : 3;
    unsigned char rank : 3;

public:
    Position(const std::string &notation)
        : file(notation[0] - 'a'), rank(notation[1] - '1')
    {}

    Position(unsigned char ch = 0)
        : file(ch & 0x7), rank((ch >> 3) & 0x7)
    {}

    Position(unsigned char file_, unsigned char rank_)
        : file(file_ & 0x7), rank(rank_ & 0x7)
    {}

    Position(const Position &rhs)
        : file(rhs.file), rank(rhs.rank)
    {}

    inline std::string to_string() const
    {
        return std::string({static_cast<char>('a' + file), static_cast<char>('1' + rank)});
    }

    inline operator unsigned char() const { return (rank << 3) | file; }
    inline std::uint8_t Hash() const { return (rank << 3) | file; }

    inline unsigned char getFile() const { return file; }
    inline unsigned char getRank() const { return rank; }

    bool safeToAdd(char dfile, char drank) const;
    bool safeToAdd(Position dp) const;

    Position add(char dfile, char drank) const;
    Position add(Position dp) const;
};

#endif