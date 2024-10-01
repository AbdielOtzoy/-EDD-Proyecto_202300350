#ifndef LISTNODE_H
#define LISTNODE_H

#include <iostream> // Tell the copiler to use I/O functions
#include "../matrix/matrixnode.h"
using namespace std;

class ListNode
{
private:
    /* data */
public:
    // CONSTRUCTORS
    ListNode();            // Default constructor
    ListNode(string name); // Constructor with parameters
    // VARIABLES
    string name;
    ListNode *next;
    MatrixNode *access;
};

#endif // LISTNODE_H
