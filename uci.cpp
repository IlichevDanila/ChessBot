#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Declarations.hpp"
#include "Position.hpp"
#include "Piece.hpp"
#include "Move.hpp"
#include "Board.hpp"
#include "Searcher.hpp"

#define LOG(str) log = std::ofstream("P:\\ChessBot\\Log.txt", std::ios_base::app); \
                 log << str << std::endl; \
                 log.close();       

int main()
{
    std::ofstream log("Log.txt");
    log.close();

    std::string message;
    std::vector<std::string> commands;

    Board board = Board::startingBoard();
    Searcher searcher;

    while(std::getline(std::cin, message) && message != "quit")
    {
        commands.clear();
        LOG("Recieved: " << message)
        int prevDel = -1;
        int currDel = 0;
        for(
            currDel = message.find(' ');
            currDel != message.npos;
            currDel = message.find(' ', prevDel + 1)
        )
        {
            commands.push_back(message.substr(prevDel + 1, currDel - prevDel - 1));
            prevDel = currDel;
        }
        if(prevDel != message.size() - 1)
        {
            commands.push_back(message.substr(prevDel + 1));
        }

        if(commands[0] == "quit")
        {
            break;
        }
        else if(commands[0] == "uci")
        {
            std::cout << "uciok" << std::endl;
            LOG("Reply: " << "uciok")
        }
        else if(commands[0] == "isready")
        {
            std::cout << "readyok" << std::endl;
            LOG("Reply: " << "readyok")
        }
        else if(commands[0] == "position")
        {
            int nextComm = 1;
            if(commands[1] == "fen")
            {
                board = Board::fromFEN(commands[2], commands[3][0], commands[4], commands[5][0], std::stoi(commands[6]), std::stoi(commands[7]));
                nextComm = 8;
            }
            else if(commands[1] == "startpos")
            {
                board = Board::startingBoard();
                nextComm = 2;
            }
            else
            {
                std::cout << "Invalid position command" << std::endl;
                LOG("Reply: " << "Invalid position command")
                return -1;
            }

            if(commands.size() > nextComm && commands[nextComm] == "moves")
            {
                ++nextComm;
                while(nextComm < commands.size())
                {
                    board = board.doMove(Move::FromNotation(commands[nextComm], board));
                    ++nextComm;
                }
            }
        }
        else if(commands[0] == "go")
        {
            Move bestMove = searcher.getBestMove(board, board.currentColor(), 2);
            std::cout << "bestmove " << bestMove.ToNotation() << std::endl;
            LOG("Reply: " << "bestmove " << bestMove.ToNotation())
        }
        else if(commands[0] == "quit")
        {
            return 0;
        }
    }

    return 0;
}