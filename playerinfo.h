#ifndef PLAYERINFO_H
#define PLAYERINFO_H
#include <map>
#include <string>
#include "bounds.h"

class PlayerInfo
{
public:
    std::map <char, Bounds > length;
    Bounds hcp;

    PlayerInfo();
    bool suitValid(char suit);
    void setLength(char suit, int lower, int upper);
    void setHcp(int lower, int upper);


};

#endif // PLAYERINFO_H
