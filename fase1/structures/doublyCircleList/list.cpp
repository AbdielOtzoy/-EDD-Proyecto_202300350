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
    cout << endl;
    cout << "Autor: " << post.getAuthor() << endl;
    cout << "Contenido: " << post.getContent() << endl;
    cout << "Fecha: " << post.getDate() << endl;
    cout << "Hora: " << post.getTime() << endl;
    cout << endl;
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
    // imprimir la lista de publicaciones, tener opciones de anterior y siguiente
    if (this->head == nullptr)
    {
        cout << "No hay publicaciones disponibles" << endl;
        return;
    }
    DoubleNode *current = this->head;
    do
    {
        current->printNode();
        cout << "1. Anterior" << endl;
        cout << "2. Siguiente" << endl;
        cout << "3. Volver" << endl;
        cout << "Opcion: ";
        int opcion;
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            current = current->prev;
            break;
        case 2:
            current = current->next;
            break;
        case 3:
            return;
        default:
            cout << "Opcion no valida" << endl;
        }
    } while (true);
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