#ifndef STACK_H
#define STACK_H

#include "../../models/headers/Request.h"

class NodeStack
{
public:
    Request request;
    NodeStack *next;
    NodeStack(Request request);
};

class Stack
{
private:
    NodeStack *top;

public:
    Stack();
    void push(Request request);
    Request pop();
    Request peek();
    bool isEmpty();
    void printStack();
    void createDotFile();
};

#endif
