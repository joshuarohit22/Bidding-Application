#include "playerinfo.h"
#include <iostream>
#include <string>

PlayerInfo::PlayerInfo() : hcp(0, 37)
{
    char suits[] = {'C', 'D', 'H', 'S', 'N'};

    for (auto s : suits)
    {
        length[s] = Bounds(0, 13);
    }

}

bool PlayerInfo::suitValid(char suit)
{
    if (suit == 'C' || suit == 'D' || suit == 'H' || suit == 'S' || suit == 'N'|| suit == 'X' || suit == 'P'|| suit == 'R')
    {
        return true;
    }
    return false;
}

void PlayerInfo::setLength(char suit, int lower, int upper)
{
    if (!suitValid(suit))
    {
        std::cout << "suit invalid" << std::endl;
        return;
    }

    length[suit].setBounds(lower, upper);
}

void PlayerInfo::setHcp(int lower, int upper)
{
    hcp.setBounds(lower, upper);
}
