#ifndef CIRCULAR_DOUBLY_LINKED_LIST_H
#define CIRCULAR_DOUBLY_LINKED_LIST_H

#include <iostream>
#include "../../models/headers/Post.h"

// Estructura del nodo
struct DoubleNode
{
private:
public:
    Post post;
    DoubleNode *next;
    DoubleNode *prev;

    DoubleNode();
    DoubleNode(Post post);
    void printNode();
};

// Estructura de la lista
class DoublyCircleList
{
private:
public:
    DoubleNode *head;

    DoublyCircleList();
    void insert(Post post);
    void printList();
    void clear();
    bool isEmpty();
    void createDotFile();

    ~DoublyCircleList();
};

#endif
