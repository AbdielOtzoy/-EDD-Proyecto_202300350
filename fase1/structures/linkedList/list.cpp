#include <iostream>
#include <string>
#include "./headers/list.h"
#include "../../models/headers/User.h"

using namespace std;

LinkedList::LinkedList()
{
    this->head = NULL;
    this->size = 0;
}

void LinkedList::insert(User user)
{
    Node *newNode = new Node(user);
    if (this->head == NULL)
    {
        this->head = newNode;
    }
    else
    {
        Node *current = this->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }
    this->size++;
}

void LinkedList::printList()
{
    Node *current = this->head;
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

void LinkedList::remove(string email)
{
    Node *current = this->head;
    Node *previous = NULL;
    while (current != NULL)
    {
        if (current->user.getEmail() == email)
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

Node *LinkedList::search(string email)
{
    Node *current = this->head;
    while (current != NULL)
    {
        if (current->user.getEmail() == email)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int LinkedList::getSize()
{
    return this->size;
}
