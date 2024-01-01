#include "Utils.hpp"

std::list<std::string> split(std::string str, char del)
{
    std::list<std::string> res;

    size_t pos = 0;
    while ((pos = str.find(del)) != std::string::npos) {
        res.push_back(str.substr(0, pos));
        str.erase(0, pos + 1);
    }
    res.push_back(str);

    return res;
}