#ifndef SIMPLELIST_H
#define SIMPLELIST_H

#include "listnode.h"
class SimpleList
{
private:
public:
    // DEFAULT CONSTRUCTOR
    SimpleList(int typeHeader);
    ~SimpleList();
    // VARIABLES
    int size;
    int typeHeader; // row = 0 and col =1
    ListNode *head;
    ListNode *tail;
    // FUNCTIONS
    ListNode *insert(string name);
    void print();
};

#endif // SIMPLELIST_H
