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
        file << "  rankdir=LR;" << endl; // Para dibujar de izquierda a derecha, en lugar de arriba a abajo
        file << "  node [shape=box, style=filled, color=lightblue];" << endl;

        NodeList *current = this->head;
        int nodeId = 0;
        // Primero creamos los nodos
        while (current != NULL)
        {
            file << "  node" << nodeId << " [label=\"Emisor: " << current->request.getEmisor()
                 << "\\nReceptor: " << current->request.getReceptor()
                 << "\\nEstado: " << current->request.getEstado() << "\"];" << endl;
            current = current->next;
            nodeId++;
        }

        // Luego creamos las conexiones entre los nodos
        current = this->head;
        nodeId = 0;
        while (current != NULL && current->next != NULL)
        {
            file << "  node" << nodeId << " -> node" << (nodeId + 1) << ";" << endl;
            current = current->next;
            nodeId++;
        }
        file << "}" << endl;
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