#include <iostream>
#include <string>
#include "./list.h"
#include "../../models/headers/Post.h"

using namespace std;

DoubleNode::DoubleNode()
{
    this->post = Post();
    this->next = nullptr;
    this->prev = nullptr;
}

DoubleNode::DoubleNode(Post post)
{
    this->post = post;
    this->next = nullptr;
    this->prev = nullptr;
}

void DoubleNode::printNode()
{
    cout << "Contenido: " << post.getContent() << endl;
    cout << "Fecha: " << post.getDate() << endl;
}

DoublyCircleList::DoublyCircleList()
{
    this->head = nullptr;
}

void DoublyCircleList::insert(Post post)
{
    DoubleNode *newNode = new DoubleNode(post);
    if (this->head == nullptr)
    {
        this->head = newNode;
        this->head->next = this->head;
        this->head->prev = this->head;
    }
    else
    {
        DoubleNode *current = this->head;
        while (current->next != this->head)
        {
            current = current->next;
        }
        current->next = newNode;
        newNode->prev = current;
        newNode->next = this->head;
        this->head->prev = newNode;
    }
}

void DoublyCircleList::printList()
{
    DoubleNode *current = this->head;
    do
    {
        current->printNode();
        current = current->next;
    } while (current != this->head);
}

DoublyCircleList::~DoublyCircleList()
{
    DoubleNode *current = this->head;
    while (current->next != this->head)
    {
        DoubleNode *temp = current;
        current = current->next;
        delete temp;
    }
    delete current;
}

void DoublyCircleList::clear()
{
    DoubleNode *current = this->head;
    while (current->next != this->head)
    {
        DoubleNode *temp = current;
        current = current->next;
        delete temp;
    }
    delete current;
    this->head = nullptr;
}

bool DoublyCircleList::isEmpty()
{
    return this->head == nullptr;
}