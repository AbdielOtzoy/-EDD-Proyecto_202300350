#include <iostream>
#include <string>
#include <fstream>
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

// implementacion de la funcion createDotFile
void List::createDotFile()
{
    ofstream file;
    file.open("solicitudes_enviadas.dot");
    if (file.is_open())
    {
        file << "digraph G {" << endl;
        NodeList *current = this->head;
        // el emisor y receptor tienen caracteres especiales que deben ser escapados
        while (current != NULL)
        {
            file << "\"" << current->request.getEmisor() << " " << current->request.getReceptor() << "\" [label=\"" << current->request.getEstado() << "\"];" << endl;
            current = current->next;
        }
        current = this->head;
        while (current != NULL)
        {
            if (current->next != NULL)
            {
                file << "\"" << current->request.getEmisor() << " " << current->request.getReceptor() << "\" -> \"" << current->next->request.getEmisor() << " " << current->next->request.getReceptor() << "\";" << endl;
            }
            current = current->next;
        }
        file << "}";
        file.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo" << endl;
    }
}

bool List::isEmpty()
{
    return this->head == NULL;
}