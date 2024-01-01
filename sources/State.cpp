#include "Declarations.hpp"
#include "State.hpp"
#include "Utils.hpp"

State::State(
    const std::string &board,
    const std::string &side,
    const std::string &castlings,
    const std::string &ep
)
{
    int rank = Rank::Rank_8;
    int file = File::File_A;
    for(auto line: split(board, '/'))
    {
        for(auto ch: line)
        {
            if(ch >= '0' && ch <= '9')
            {
                file += ch;
            }
            else
            {
                squares[(rank << 3) | file] = Piece(ch);
            }
        }
        --rank;
        file = File::File_A;
    }

    
}

std::string State::getString() const
{

}