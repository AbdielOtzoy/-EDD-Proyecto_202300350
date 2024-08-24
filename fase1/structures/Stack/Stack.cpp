#include <iostream>
#include <string>
#include "../../models/headers/Request.h"
#include "./Stack.h"

using namespace std;

NodeStack::NodeStack(Request request)
{
    this->request = request;
    this->next = NULL;
}

Stack::Stack()
{
    this->top = NULL;
}

void Stack::push(Request request)
{
    NodeStack *newNodeStack = new NodeStack(request);
    newNodeStack->next = this->top;
    this->top = newNodeStack;
}

Request Stack::pop()
{
    if (this->top == NULL)
    {
        cout << "Stack is empty" << endl;
        return Request();
    }
    NodeStack *temp = this->top;
    this->top = this->top->next;
    Request request = temp->request;
    delete temp;
    return request;
}

Request Stack::peek()
{
    if (this->top == NULL)
    {
        cout << "Stack is empty" << endl;
        return Request();
    }
    return this->top->request;
}

bool Stack::isEmpty()
{
    return this->top == NULL;
}

void Stack::printStack()
{
    NodeStack *current = this->top;
    while (current != NULL)
    {
        cout << current->request.getEstado() << " -> " << current->request.getReceptor() << endl;
        current = current->next;
    }
}