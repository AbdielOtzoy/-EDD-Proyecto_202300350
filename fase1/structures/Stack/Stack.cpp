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

// implementacion de la funcion createDotFile
void Stack::createDotFile()
{
    ofstream file;
    file.open("solicitudes_recibidas.dot");
    if (file.is_open())
    {
        file << "digraph G {" << endl;
        NodeStack *current = this->top;
        // el emisor y receptor tienen caracteres especiales que deben ser escapados
        while (current != NULL)
        {
            file << "\"" << current->request.getEmisor() << " " << current->request.getReceptor() << "\" [label=\"" << current->request.getEstado() << "\"];" << endl;
            current = current->next;
        }
        current = this->top;

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