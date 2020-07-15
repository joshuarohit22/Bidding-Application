#ifndef BID_H
#define BID_H
#include <string>

class Bid
{
private:
    int level;
    //'C' for Clubs, 'D' for Diamonds, 'H' for Hearts, 'S' for Spades, 'N' for Notrump, 'P' for pass, 'X' for double, 'R' for redouble
    char suit;
public:
    Bid();
    Bid(int level, char suit);
    Bid(std::string bidStr);
    void setLevel(int level);
    void setSuit(char suit);
    void setBid(int level, char suit);
    bool suitValid(char suit);
    int getLevel();
    char getSuit();
    std::string getBid();
};

#endif // BID_H
