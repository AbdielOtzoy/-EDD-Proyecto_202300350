#include <iostream>
#include <string>
#include <fstream>
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

// implementacion de la funcion createDotFile
void LinkedList::createDotFile()
{
    ofstream file;
    file.open("usuarios.dot");
    if (file.is_open())
    {
        file << "digraph G {" << endl;
        Node *current = this->head;
        while (current != NULL)
        {
            file << current->user.getName() << " [label=\"" << current->user.getName() << "\"];" << endl;
            current = current->next;
        }
        current = this->head;
        while (current != NULL)
        {
            if (current->next != NULL)
            {
                file << current->user.getName() << " -> " << current->next->user.getName() << ";" << endl;
            }
            current = current->next;
        }
        file << "}";
        file.close();
    }
    else
    {
        cout << "Error al abrir el archivo" << endl;
    }
}

void LinkedList::topFiveUsersWithLeastFriends()
{
    cout << "Top 5 usuarios con menos amigos :c" << endl;
}