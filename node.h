#ifndef NODE_H
#define NODE_H
#include "playerinfo.h"
#include <vector>

class Node
{
public:
    PlayerInfo currInfo;
    int index;
    std::string changes;
    std::string bid;
    std::string type;
    std::string typeInfo;
    std::vector <Node *> children;
    std::vector <Node *> parent;
    bool artificial;
    bool saved;
    bool color;

    Node(std::string bid, std::string changes);
    void addNode(Node *newNode);
    Node *getChild(std::string bid);
    int saveChanges(std::string str);
    std::vector <int> parseRange(std::string s);
    void parseInput(std::string str);

};

#endif // NODE_H
