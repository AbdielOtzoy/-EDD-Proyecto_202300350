#include <iostream>
#include <string>
#include "./headers/list.h"
#include "../../models/headers/Post.h"
#include "../doublyCircleList/list.h"

using namespace std;

DoublyList::DoublyList()
{
    this->head = NULL;
    this->tail = NULL;
}

void DoublyList::addNode(Post post)
{
    NodeDoubly *newNode = new NodeDoubly(post);
    if (this->head == NULL)
    {
        this->head = newNode;
        this->tail = newNode;
    }
    else
    {
        this->tail->next = newNode;
        newNode->prev = this->tail;
        this->tail = newNode;
    }
}

void DoublyList::printList()
{
    NodeDoubly *current = this->head;
    while (current != NULL)
    {
        current->printNodeDoubly();
        current = current->next;
    }
}

void DoublyList::deleteNode(string author)
{
    NodeDoubly *current = this->head;
    while (current != NULL)
    {
        if (current->post.getAuthor() == author)
        {
            if (current == this->head)
            {
                this->head = current->next;
                this->head->prev = NULL;
            }
            else if (current == this->tail)
            {
                this->tail = current->prev;
                this->tail->next = NULL;
            }
            else
            {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            delete current;
            return;
        }
        current = current->next;
    }
}

void DoublyList::searchNode(string author)
{
    NodeDoubly *current = this->head;
    while (current != NULL)
    {
        if (current->post.getAuthor() == author)
        {
            current->printNodeDoubly();
            return;
        }
        current = current->next;
    }
    cout << "No se encontro el post" << endl;
}

// Filtrar posts por autor e insertarlos en una lista circular doblemente enlazada
void DoublyList::filterByAuthor(string author, DoublyCircleList &list)
{
    NodeDoubly *current = this->head;
    while (current != NULL)
    {
        if (current->post.getAuthor() == author)
        {
            list.insert(current->post);
        }
        current = current->next;
    }
}