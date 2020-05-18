#include "playerinfo.h"
#include <string>

PlayerInfo::PlayerInfo() : hcp(0, 37)
{
    std::string suits[] = {"CLUBS", "DIAMONDS", "HEARTS", "SPADES"};

    for (auto s : suits)
    {
        length[s] = bounds(0, 13);
    }

//    struct bounds temp(0, 13);
//    length["CLUBS"] = temp;
//    length["DIAMONDS"] = temp;
//    length["HEARTS"] = temp;
//    length["SPADES"] = temp;

}
