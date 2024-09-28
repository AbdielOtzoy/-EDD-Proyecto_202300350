#include "stack.h"
#include <string>
#include <fstream>
#include <QDebug>
#include <QTableWidget>
#include "../appstage.h"
#include "../models/request.h"

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
        qDebug() << "Stack is empty";
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
        qDebug() << "Stack is empty";
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
        qDebug() << "Emisor: " << current->request.getEmisor();
        qDebug() << "Receptor: " << current->request.getReceptor();
        qDebug() << "Estado: " << current->request.getEstado();
        current = current->next;
    }
}

// Nueva función para eliminar un Request específico
void Stack::remove(Request request)
{
    if (this->top == NULL)
    {
        qDebug() << "Stack is empty";
        return;
    }

    // Caso especial: si el nodo a eliminar es el top
    if (this->top->request.getEmisor() == request.getEmisor() &&
        this->top->request.getReceptor() == request.getReceptor() &&
        this->top->request.getEstado() == request.getEstado())
    {
        NodeStack *temp = this->top;
        this->top = this->top->next;
        delete temp;
        qDebug() << "Request removed from the stack.";
        return;
    }

    // Recorrer la pila para encontrar y eliminar el nodo
    NodeStack *current = this->top;
    while (current->next != NULL)
    {
        if (current->next->request.getEmisor() == request.getEmisor() &&
            current->next->request.getReceptor() == request.getReceptor() &&
            current->next->request.getEstado() == request.getEstado())
        {
            NodeStack *temp = current->next;
            current->next = current->next->next;
            delete temp;
            qDebug() << "Request removed from the stack.";
            return;
        }
        current = current->next;
    }

    qDebug() << "Request not found in the stack.";
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
        qDebug() << "No se pudo abrir el archivo";
    }
}

void Stack::agregarSolicitudTabla(QTableWidget *table, User *userlogged) {
    NodeStack *current = this->top;
    AppState *appstate = AppState::getInstance();
    Avl *avlTree = appstate->getAvlTree();

    while (current != NULL)
    {
        int row = table->rowCount();
        table->insertRow(row);

        table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(current->request.getEmisor())));
        // agregar botón para cancelar la solicitud
        QPushButton *cancelarBtn = new QPushButton("Cancelar");
        // agregar bot0on para aceptar la solicitud
        QPushButton *aceptarBtn = new QPushButton("Aceptar");

        // Conectar el botón a una función lambda para manejar el cancelar la solicitud
        QObject::connect(cancelarBtn, &QPushButton::clicked, [current, userlogged, avlTree](){
            qDebug() << "Solicitud eliminada De: " << current->request.getEmisor();
            // implementar lógica para eliminar la solicitud de ambos usuarios
            userlogged->requestsReceived.remove(current->request); // eliminar para el usuario logeado

            //buscar el usuario de la solicitud enviada
            Nodo userReceptor = avlTree->buscar(current->request.getEmisor());
            if(userReceptor != NULL) {
                userReceptor->data.removeRequestSent(current->request);
                qDebug() << "solicitud quitada con éxito";
            }

        });

        // Conectar el botón a una función lambda para manejar el envío de solicitud
        QObject::connect(aceptarBtn, &QPushButton::clicked, [current, userlogged, avlTree](){
            qDebug() << "Solicitud aceptada De: " << current->request.getEmisor();
            // implementar lógica para hacer amigos a ambos usuarios
            userlogged->addFriend(current->request.getEmisor());
            userlogged->requestsReceived.remove(current->request);
            //buscar el usuario de la solicitud enviada
            Nodo userReceptor = avlTree->buscar(current->request.getEmisor());
            if(userReceptor != NULL) {
                userReceptor->data.addFriend(userlogged->getEmail());
                userReceptor->data.removeRequestSent(current->request);
                qDebug() << "solicitud aceptada con éxito";
            }

        });
        table->setCellWidget(row, 1, cancelarBtn);
        table->setCellWidget(row, 2, aceptarBtn);

        current = current->next;
    }

}
