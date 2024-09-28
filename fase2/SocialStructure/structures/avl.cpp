#include "avl.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <QDebug>
#include "../user.h"
#include <QTableWidget>
#include <QPushButton>
#include "../models/request.h"

using namespace std;

Avl::Avl()
{
    Raiz = NULL;
}

void Avl::ver()
{
    inOrden(Raiz);
}

void Avl::inOrden(Nodo &aux)
{
    if (aux != NULL)
    {
        inOrden(aux->Izq);
        aux->data.printUser(); // Imprime los datos del usuario
        inOrden(aux->Der);
    }
}

Nodo Avl::buscar(string email)
{
    return buscar(Raiz, email);
}

Nodo Avl::buscar(Nodo &aux, string email)
{
    if (aux == NULL)
    {
        return NULL; // Return NULL if the node is not found
    }
    else if (email == aux->data.getEmail())
    {
        return aux;
    }
    else if (compararStrings(email, aux->data.getEmail()) < 0) // Corrected comparison
    {
        return buscar(aux->Izq, email);
    }
    else
    {
        return buscar(aux->Der, email);
    }
}


// Método público para agregar un usuario
void Avl::agregar(User user) {
    try {
        Raiz = agregar(Raiz, user);
    } catch (const char *e) {
        qDebug() << e;
    }
}

// Método privado recursivo para agregar un usuario
Nodo Avl::agregar(Nodo &aux, User user) {
    if (aux == NULL) {
        aux = new nodo;
        aux->data = user; // Asignamos el objeto User
        aux->Der = NULL;
        aux->Izq = NULL;
        return aux;
    }

    // Comparamos los correos directamente
    if (user.getEmail() < aux->data.getEmail()) {
        aux->Izq = agregar(aux->Izq, user);
    }
    else if (user.getEmail() > aux->data.getEmail()) {
        aux->Der = agregar(aux->Der, user);
    }
    else {
        // Los correos son iguales, no se puede agregar
        throw "Nodo duplicado: El usuario con este correo ya existe.";
    }

    // Asegurar el balance del AVL aquí si es necesario
    return aux;
}

// Función para comparar dos strings, no es realmente necesaria
// dado que podemos usar directamente las operaciones de comparación estándar
bool Avl::compararStrings(string str1, string str2) {
    return str1 > str2; // Comparación lexicográfica
}

int Avl::canNivel(Nodo aux)
{
    if (aux != NULL)
    {
        int izq = canNivel(aux->Izq) + 1;
        int der = canNivel(aux->Der) + 1;
        if (izq > der)
            return izq;
        return der;
    }
    return -1;
}

void Avl::verNivel(Nodo aux, int n)
{
    if (aux != NULL)
    {
        if (n == 0)
            qDebug() << aux->data.getEmail() << " "; // Imprime el correo del usuario
        verNivel(aux->Izq, n - 1);
        verNivel(aux->Der, n - 1);
    }
}

void Avl::elimina()
{
    elimina(Raiz);
}

void Avl::elimina(Nodo &aux)
{
    if (aux != NULL)
    {
        elimina(aux->Izq);
        delete aux;
        elimina(aux->Der);
    }
}

Nodo Avl::getRaiz()
{
    return Raiz;
}

int Avl::nodoN(Nodo aux, int n)
{
    if (aux != NULL)
    {
        if (n == 0)
            return nodoN(aux->Izq, n - 1) + nodoN(aux->Der, n - 1) + 1;
        return nodoN(aux->Izq, n - 1) + nodoN(aux->Der, n - 1);
    }
    return 0;
}

int Avl::numNoN(Nodo aux, int n)
{
    if (aux != NULL)
    {
        if (n <= 0)
            return numNoN(aux->Izq, n - 1) + numNoN(aux->Der, n - 1) + 1;
        return numNoN(aux->Izq, n - 1) + numNoN(aux->Der, n - 1);
    }
    return 0;
}

void Avl::graficarDot()
{
    ofstream archivo;
    archivo.open("Avl.dot", ios::out);
    if (archivo.fail())
    {
        exit(1);
    }
    archivo << "digraph G {" << endl;
    stringstream ss;
    graficarDot(Raiz, ss);
    archivo << ss.str();
    archivo << "}" << endl;
    archivo.close();
    system("dot -Tpng Avl.dot -o Avl.png");
}

void Avl::graficarDot(Nodo aux, stringstream &ss)
{
    if (aux != NULL)
    {
        string sanitizedEmail = aux->data.getEmail();

        // Reemplazamos caracteres especiales por guiones bajos
        for (char &c : sanitizedEmail)
        {
            if (!isalnum(c)) // Si no es alfanumérico, lo reemplazamos por '_'
                c = '_';
        }

        // Usamos el correo sanitizado como identificador del nodo
        ss << sanitizedEmail << "[label=\"" << aux->data.getEmail() << "\"];" << endl;

        if (aux->Izq != NULL)
        {
            string sanitizedEmailIzq = aux->Izq->data.getEmail();
            for (char &c : sanitizedEmailIzq)
            {
                if (!isalnum(c))
                    c = '_';
            }
            ss << sanitizedEmail << "->" << sanitizedEmailIzq << ";" << endl;
        }

        if (aux->Der != NULL)
        {
            string sanitizedEmailDer = aux->Der->data.getEmail();
            for (char &c : sanitizedEmailDer)
            {
                if (!isalnum(c))
                    c = '_';
            }
            ss << sanitizedEmail << "->" << sanitizedEmailDer << ";" << endl;
        }

        graficarDot(aux->Izq, ss);
        graficarDot(aux->Der, ss);
    }
}

void Avl::agregarUsuariosATabla(QTableWidget *table, User *userLogged) {
    agregarUsuariosATabla(Raiz, table, userLogged);
}

void Avl::agregarUsuariosATabla(Nodo &aux, QTableWidget *table, User *userLogged) {
    if (aux != NULL) {
        // Recorrer el subárbol izquierdo
        agregarUsuariosATabla(aux->Izq, table, userLogged);

        // Verificar que no sea el usuario logueado
        if (aux->data.getEmail() != userLogged->getEmail()) {
            int row = table->rowCount(); // Obtiene el número actual de filas
            table->insertRow(row); // Inserta una nueva fila al final de la tabla

            // Agrega los datos a cada celda de la fila
            table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(aux->data.getName())));
            table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(aux->data.getLastName())));
            table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(aux->data.getEmail())));
            table->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(aux->data.getBirthDate())));

            // Crear un botón para la última columna
            QPushButton* sendRequestButton = new QPushButton("Enviar solicitud");

            // Conectar el botón a una función lambda para manejar el envío de solicitud
            QObject::connect(sendRequestButton, &QPushButton::clicked, [table, row, &aux, userLogged](){
                qDebug() << "Solicitud enviada a: " << QString::fromStdString(aux->data.getEmail());
                // Aquí puedes agregar lógica para enviar la solicitud al usuario aux->data
                Request *request = new Request(userLogged->getEmail(), aux->data.getEmail(), "pendiente");
                request->printRequest();

                userLogged->addRequestSent(*request);
                aux->data.addRequestReceived(*request);
            });
            // Inserta el botón en la última columna de la fila
            table->setCellWidget(row, 4, sendRequestButton);
        }

        // Recorrer el subárbol derecho
        agregarUsuariosATabla(aux->Der, table, userLogged);
    }
}

Avl::~Avl()
{
    elimina();
}
