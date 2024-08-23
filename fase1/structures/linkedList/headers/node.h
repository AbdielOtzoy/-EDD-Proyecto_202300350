#ifndef NODE_H
#define NODE_H

#include "../../../models/headers/User.h"
class Node
{
private:
public:
    User user;
    Node *next;

    Node();
    Node(User user);

    void printNode();
};

#endif