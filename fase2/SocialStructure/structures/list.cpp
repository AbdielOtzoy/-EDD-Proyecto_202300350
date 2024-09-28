#include "list.h"
#include "../models/request.h"
#include "../user.h"
#include <QDebug>
#include <fstream>
#include <QTableWidget>
#include <QPushButton>
#include <QString>
#include "../appstage.h"
#include "avl.h"

using namespace std;

NodeList::NodeList()
{
    this->next = NULL;
}

NodeList::NodeList(Request request)
{
    this->request = request;
    this->next = NULL;
}

void NodeList::printNode()
{
    qDebug() << "Emisor: " << this->request.getEmisor();
    qDebug() << "Receptor: " << this->request.getReceptor();
    qDebug() << "Estado: " << this->request.getEstado();
    qDebug() << "--------------------------------";
}


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
        qDebug() << "Lista vacia";
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
        qDebug() << "No se pudo abrir el archivo";
    }
}

void List::agregarSolicitudTabla(QTableWidget *table, User *userlogged) {
    NodeList *current = this->head;
    AppState *appstate = AppState::getInstance();
    Avl *avlTree = appstate->getAvlTree();

    if (this->head == NULL)
    {
        qDebug() << "Lista vacia";
        return;
    }
    while (current != NULL)
    {
        int row = table->rowCount();
        table->insertRow(row);

        //agregar las solicitudes enviadas
        table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(current->request.getReceptor())));

        // agregar botón para cancelar la solicitud
        QPushButton *cancelarBtn = new QPushButton("Cancelar");

        // Conectar el botón a una función lambda para manejar el envío de solicitud
        QObject::connect(cancelarBtn, &QPushButton::clicked, [current, userlogged, avlTree](){
            qDebug() << "Solicitud cancelada hacia: " << current->request.getReceptor();
            // implementar lógica para eliminar la solicitud de ambos usuarios
            userlogged->removeRequestSent(current->request); // solicitud enviada

            //buscar el usuario de la solicitud enviada
            Nodo userReceptor = avlTree->buscar(current->request.getReceptor());
            if(userReceptor != NULL) {
                userReceptor->data.requestsReceived.remove(current->request);
                qDebug() << "solicitud quitada con éxito";
            }

        });
        // Inserta el botón en la última columna de la fila
        table->setCellWidget(row, 1, cancelarBtn);
        current = current->next;


    }
}

bool List::isEmpty()
{
    return this->head == NULL;
}
