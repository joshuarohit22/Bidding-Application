#ifndef PLAYERINFO_H
#define PLAYERINFO_H
#include <map>
#include <string>
#include "bounds.h"

class PlayerInfo
{
public:
    std::map <std::string, bounds > length;
    struct bounds hcp;

    PlayerInfo();


};

#endif // PLAYERINFO_H
