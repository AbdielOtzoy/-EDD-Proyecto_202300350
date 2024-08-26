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

// implementacion de la funcion topFiveUsersWithLeastFriends, muestra los 5 usuarios con menos amigos
// utiliza la función getSizeFriends de User para obtener la cantidad de amigos de cada usuario
void LinkedList::topFiveUsersWithLeastFriends()
{
    Node *current = this->head;
    User *users[this->size];
    int i = 0;
    while (current != NULL)
    {
        users[i] = &current->user;
        current = current->next;
        i++;
    }
    for (int i = 0; i < this->size; i++)
    {
        for (int j = i + 1; j < this->size; j++)
        {
            if (users[i]->getSizeFriends() > users[j]->getSizeFriends())
            {
                User *temp = users[i];
                users[i] = users[j];
                users[j] = temp;
            }
        }
    }
    for (int i = 0; i < 5; i++)
    {
        cout << "Usuario: " << users[i]->getName() << " Amigos: " << users[i]->getSizeFriends() << endl;
    }
}
