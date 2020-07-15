#include "bid.h"
#include <sstream>

Bid::Bid()
{

}

Bid::Bid(int level, char suit)
{
    if (suitValid(suit))
    {
        this->level = level;
        this->suit = suit;
    }
    else
    {
        this->level = -1;
        this->suit = '$';
    }
}

Bid::Bid(std::string bidStr)
{
    if (bidStr == "Pass")
    {
        this->level = -1;
        this->suit = 'P';
    }
    else if (bidStr == "Dbl")
    {
        this->level = -1;
        this->suit = 'X';
    }
    else if (bidStr == "RDbl")
    {
        this->level = -1;
        this->suit = 'R';
    }
    else
    {
        std::string strLevel = bidStr.substr(0,1);
        std::stringstream geek(strLevel);

        geek >> this->level;

        this->suit = bidStr[1];

    }

}

void Bid::setLevel(int level)
{
    this->level = level;
}

void Bid::setSuit(char suit)
{
    if (suitValid(suit))
    {
        this->suit = suit;
        if (this->suit == 'X' || this->suit == 'R' || this->suit == 'P')
        {
            this->level = -1;
        }
    }
}

void Bid::setBid(int level, char suit)
{
    if (suitValid(suit))
    {
        this->level = level;
        this->suit = suit;
        if (this->suit == 'X' || this->suit == 'R' || this->suit == 'P')
        {
            this->level = -1;
        }
    }
}

int Bid::getLevel()
{
    return this->level;
}

char Bid::getSuit()
{
    return this->suit;
}

std::string Bid::getBid()
{
    if (this->level > 0)
        return std::to_string(level) + this->suit;
    else if (this->suit == 'X')
        return "Dbl";
    else if (this->suit == 'R')
        return "RDbl";
    else if (this->suit == 'P')
        return "Pass";
    else
        return "Invalid";
}

bool Bid::suitValid(char suit)
{
    if (suit == 'C' || suit == 'D' || suit == 'H' || suit == 'S' || suit == 'N' || suit == 'X' || suit == 'P'|| suit == 'R')
    {
        return true;
    }
    return false;
}
