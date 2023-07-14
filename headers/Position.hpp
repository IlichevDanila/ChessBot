#ifndef POSITION_HPP
#define POSITION_HPP

class Position
{
private:
    unsigned char file : 3;
    unsigned char rank : 3;

public:
    Position(unsigned char ch = 0);
    Position(unsigned char file_, unsigned char rank_);
    Position(const Position &rhs);

    operator unsigned char() const;

    unsigned char getFile() const;
    unsigned char getRank() const;

    bool safeToAdd(char dfile, char drank) const;

    Position add(char dfile, char drank) const;

    bool operator==(const Position &rhs) const;
};

#endif