#include <iostream>
#include <string>
#include "./headers/list.h"
#include "../../models/headers/Request.h"

using namespace std;

List::List()
{
    this->head = NULL;
    this->size = 0;
}

void List::insert(Request request)
{
    NodeList *newNode = new NodeList(request);
    if (this->head == NULL)
    {
        this->head = newNode;
    }
    else
    {
        NodeList *current = this->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }
    this->size++;
}

void List::printList()
{
    NodeList *current = this->head;
    if (this->head == NULL)
    {
        cout << "Lista vacia" << endl;
        return;
    }
    while (current != NULL)
    {
        current->printNode();
        current = current->next;
    }
}

void List::remove(string emisor, string receptor)
{
    NodeList *current = this->head;
    NodeList *previous = NULL;
    while (current != NULL)
    {
        if (current->request.getEmisor() == emisor && current->request.getReceptor() == receptor)
        {
            if (previous == NULL)
            {
                this->head = current->next;
            }
            else
            {
                previous->next = current->next;
            }
            delete current;
            this->size--;
            return;
        }
        previous = current;
        current = current->next;
    }
}

int List::getSize()
{
    return this->size;
}
