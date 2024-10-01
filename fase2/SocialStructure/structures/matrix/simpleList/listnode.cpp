#include "listnode.h"

// Default constructor
ListNode::ListNode()
{
    next = nullptr;
    name = "";
    access = nullptr;
}
// Parameterised constructor
ListNode::ListNode(string name)
{
    this->name = name;
    this->next = nullptr;
    this->access = nullptr;
}
