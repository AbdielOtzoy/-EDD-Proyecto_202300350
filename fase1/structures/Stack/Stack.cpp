#include <iostream>
#include <string>
#include <fstream>
#include "../../models/headers/Request.h"
#include "./Stack.h"

using namespace std;

NodeStack::NodeStack(Request request)
{
    this->request = request;
    this->next = NULL;
}

Stack::Stack()
{
    this->top = NULL;
}

void Stack::push(Request request)
{
    NodeStack *newNodeStack = new NodeStack(request);
    newNodeStack->next = this->top;
    this->top = newNodeStack;
}

Request Stack::pop()
{
    if (this->top == NULL)
    {
        cout << "Stack is empty" << endl;
        return Request();
    }
    NodeStack *temp = this->top;
    this->top = this->top->next;
    Request request = temp->request;
    delete temp;
    return request;
}

Request Stack::peek()
{
    if (this->top == NULL)
    {
        cout << "Stack is empty" << endl;
        return Request();
    }
    return this->top->request;
}

bool Stack::isEmpty()
{
    return this->top == NULL;
}

void Stack::printStack()
{
    NodeStack *current = this->top;
    while (current != NULL)
    {
        cout << "Emisor: " << current->request.getEmisor() << endl;
        cout << "Receptor: " << current->request.getReceptor() << endl;
        cout << "Estado: " << current->request.getEstado() << endl;
        current = current->next;
    }
}

void Stack::createDotFile()
{
    ofstream file;
    file.open("solicitudes_recibidas.dot");
    if (file.is_open())
    {
        file << "digraph G {" << endl;
        file << "  rankdir=TB;" << endl;                                          // Dirección de arriba hacia abajo
        file << "  node [shape=record, style=filled, color=lightcoral];" << endl; // Estilo de los nodos

        NodeStack *current = this->top;
        int nodeId = 0;

        // Crear nodos con identificadores únicos
        while (current != NULL)
        {
            file << "  node" << nodeId << " [label=\"{"
                 << "Emisor: " << current->request.getEmisor() << "|"
                 << "Receptor: " << current->request.getReceptor() << "|"
                 << "Estado: " << current->request.getEstado() << "}\"];" << endl;
            current = current->next;
            nodeId++;
        }

        // Crear conexiones entre nodos para representar la pila
        current = this->top;
        nodeId = 0;
        while (current != NULL && current->next != NULL)
        {
            file << "  node" << nodeId << " -> node" << (nodeId + 1) << " [dir=back];" << endl; // Usar dir=back para mostrar dirección de la pila
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
