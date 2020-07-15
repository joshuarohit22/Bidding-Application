#ifndef NODE_H
#define NODE_H
#include "playerinfo.h"
#include "bid.h"
#include <vector>

//enum bidType {OPENING, DESCRIPTIVE, SIGNOFF, PREEMPTIVE, INVITATIONAL, FORCING, ASKING, TRANSFER, CUE, LEADDIRECTING};

class Node
{
public:
    PlayerInfo currInfo;
    int index;
    std::string changes;
    std::string bid_type;
    std::string bid_info;
    std::string comments;
    Bid bid;
    std::string type;
    std::string typeInfo;
    std::vector <Node *> children;
    std::vector <Node *> parent;
    bool artificial;
    bool saved;
    bool color;

    Node(Bid Bid);
    void addNode(Node *newNode);
    Node *getChild(std::string bidStr);
//    int saveChanges(std::string str);
//    std::vector <int> parseRange(std::string s);
//    void parseInput(std::string str);

};

#endif // NODE_H
