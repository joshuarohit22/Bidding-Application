#include "node.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <climits>
#include <regex>

Node::Node(Bid bid)
{
    this->bid = bid;
    this->changes = "";
    this->comments = "";
    this->bid_type = "";
    this->bid_info = "";
    this->saved = false;
    this->color = false;
    this->artificial = false;
}

void Node::addNode(Node *newNode)
{
    newNode->parent.push_back(this);
    this->children.push_back(newNode);
    return;
}

//std::vector <int> Node::parseRange(std::string s)
//{
////    int n = s.size();

//    std::vector <int> out;
//    int num;
//    std::string numstr;

//    std::regex r1("[0-9]+\\+");
//    std::regex r2("[0-9]+\\-");
//    std::regex r3("[0-9]+\\-[0-9]+");

////    if (!(regex_match(s, r1) || regex_match(s, r2) || regex_match(s, r3)))
////    {
////        throw "error";
////    }

//    if (regex_match(s, r1))
//    {

//        std::stringstream numstream(s);

//        while (getline(numstream, numstr, '+'))
//        {
//            num = stoi(numstr);
//            out.push_back(num);
//        }

//        out.push_back(INT_MAX);

//        return out;
//    }
//    else if (regex_match(s, r2))
//    {
//        out.push_back(-1);

//        std::stringstream numstream(s);

//        while (getline(numstream, numstr, '-'))
//        {
//            num = stoi(numstr);
//            out.push_back(num);
//        }

//        return out;
//    }
//    else if (regex_match(s, r3))
//    {
//        std::stringstream numstream(s);

//        while (getline(numstream, numstr, '-'))
//        {
//            num = stoi(numstr);
//            out.push_back(num);
//        }
//        return out;
//    }
//    else
//    {
//        throw "parsing range error";
//        return out;
////        std::cout << "error 1" << std::endl;

//    }
//}

int min(int a, int b)
{
    if (a < b)
        return a;
    return b;
}

int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

//void Node::parseInput(std::string str)
//{
//    std::vector <std::string> stmts;

//    std::stringstream parse(str);
//    std::string intermediate;

//    while (getline(parse, intermediate, ';'))
//    {
//        stmts.push_back(intermediate);
//    }

//    std::string s;

//    for (auto s : stmts)
//    {
//        std::stringstream parseStmt(s);

//        std::vector <std::string> tokens;

//        while (getline(parseStmt, intermediate, ' '))
//        {
//            if (intermediate == "")
//                continue;
//            tokens.push_back(intermediate);
//        }
//        for (auto t : tokens)
//            std::cout << t << "$";
//        std::cout << std::endl;

//        if (tokens[0] == "LENGTH")
//        {
//            std::vector <int> num_out = parseRange(tokens[2]);
//            auto it = (this->currInfo).length.find(tokens[1]);
//            if (it == (this->currInfo).length.end())
//            {
//                throw "suit not valid";
//                return;
//            }
//            (this->currInfo).length[tokens[1]].lower = max(0, num_out[0]);
//            (this->currInfo).length[tokens[1]].upper = min(13, num_out[1]);
//        }
//        else if (tokens[0] == "HCP")
//        {
//            std::vector <int> num_out = parseRange(tokens[1]);
//            this->currInfo.hcp.lower = max(0, num_out[0]);
//            this->currInfo.hcp.upper = min(37, num_out[1]);

//        }
//        else if (tokens[0] == "CATEGORY")
//        {
//            if (tokens[1] == "ARTIFICIAL")
//                this->artificial = true;
//            if (tokens[1] != "ARTIFICIAL" && tokens[1] != "NATURAL")
//            {
//                throw "must specify natural or artificial";
//                return;
////                std::cout << "error 3" << std::endl;
//            }
//            if (tokens.size() > 2)
//            {
//                this->type = tokens[2];
//                this->typeInfo = "";
//                for (unsigned i = 3;i < tokens.size();++i)
//                {
//                    this->typeInfo += tokens[i] + " ";
//                }
//                if (this->typeInfo[this->typeInfo.size()-1] == ' ')
//                    this->typeInfo.erase(this->typeInfo.begin() + this->typeInfo.size()-1);
//            }

//        }
//        else
//        {
////            std::cout << "not length or hcp" << std::endl;
//            throw "does not belong to any stmt";
//            return;
////            std::cout << "error 4" << std::endl;

//        }
//    }

//}


//int Node::saveChanges(std::string str)
//{
//    this->changes = str;
//    try {
//        parseInput(this->changes);
//    }
//    catch (std::string exception)
//    {
//        std::cout << exception << std::endl;
//        return 0;
//    }

//    catch (...) {
////        std::cout << "error 5" << std::endl;

//            return 0;


//    }
//    this->saved = true;
//    return 1;
//}

Node *Node::getChild(std::string bidStr)
{
    for (unsigned i = 0;i < this->children.size(); ++i)
    {
        if (this->children[i]->bid.getBid() == bidStr)
            return children[i];
    }

    return nullptr;
}

