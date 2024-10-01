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
    else if (email < aux->data.getEmail()) // Corrected comparison
    {
        return buscar(aux->Izq, email);
    }
    else
    {
        return buscar(aux->Der, email);
    }
}

void Avl::buscarActualizar(string email, User userUpdated) {
    Nodo userFound = buscar(email);
    userFound->data.setName(userUpdated.getName());
    userFound->data.setLastName(userUpdated.getLastName());
    userFound->data.setPassword(userUpdated.getPassword());
    userFound->data.setBirthDate(userUpdated.getBirthDate());
}


// Método público para agregar un usuario
void Avl::agregar(User user) {
    try {
        Raiz = agregar(Raiz, user);
    } catch (const char *e) {
        qDebug() << e;
    }
}

// Función para obtener la altura de un nodo
int Avl::altura(Nodo nodo) {
    if (nodo == NULL) return 0;
    return nodo->altura;
}

// Función para calcular el factor de balance de un nodo
int Avl::getBalance(Nodo nodo) {
    if (nodo == NULL) return 0;
    return altura(nodo->Izq) - altura(nodo->Der);
}

// Rotación simple a la derecha
Nodo Avl::rotacionDerecha(Nodo &y) {
    Nodo x = y->Izq;
    Nodo T2 = x->Der;

    // Realizar la rotación
    x->Der = y;
    y->Izq = T2;

    // Actualizar alturas
    y->altura = max(altura(y->Izq), altura(y->Der)) + 1;
    x->altura = max(altura(x->Izq), altura(x->Der)) + 1;

    return x; // Nueva raíz
}

// Rotación simple a la izquierda
Nodo Avl::rotacionIzquierda(Nodo &x) {
    Nodo y = x->Der;
    Nodo T2 = y->Izq;

    // Realizar la rotación
    y->Izq = x;
    x->Der = T2;

    // Actualizar alturas
    x->altura = max(altura(x->Izq), altura(x->Der)) + 1;
    y->altura = max(altura(y->Izq), altura(y->Der)) + 1;

    return y; // Nueva raíz
}

// Función para agregar y balancear el árbol
Nodo Avl::agregar(Nodo &aux, User user) {
    if (aux == NULL) {
        aux = new nodo;
        aux->data = user;
        aux->Izq = NULL;
        aux->Der = NULL;
        aux->altura = 1; // El nodo recién creado tiene altura 1
        return aux;
    }

    // Comparar correos y decidir a dónde ir
    if (user.getEmail() < aux->data.getEmail()) {
        aux->Izq = agregar(aux->Izq, user);
    } else if (user.getEmail() > aux->data.getEmail()) {
        aux->Der = agregar(aux->Der, user);
    } else {
        throw "Nodo duplicado: El usuario con este correo ya existe.";
    }

    // Actualizar la altura del nodo actual
    aux->altura = 1 + max(altura(aux->Izq), altura(aux->Der));

    // Obtener el factor de balance
    int balance = getBalance(aux);

    // Rotación a la derecha
    if (balance > 1 && user.getEmail() < aux->Izq->data.getEmail()) {
        return rotacionDerecha(aux);
    }

    // Rotación a la izquierda
    if (balance < -1 && user.getEmail() > aux->Der->data.getEmail()) {
        return rotacionIzquierda(aux);
    }

    // Rotación izquierda-derecha
    if (balance > 1 && user.getEmail() > aux->Izq->data.getEmail()) {
        aux->Izq = rotacionIzquierda(aux->Izq);
        return rotacionDerecha(aux);
    }

    // Rotación derecha-izquierda
    if (balance < -1 && user.getEmail() < aux->Der->data.getEmail()) {
        aux->Der = rotacionDerecha(aux->Der);
        return rotacionIzquierda(aux);
    }

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

Nodo Avl::eliminar(Nodo &raiz, string email) {
    // Paso 1: Realizar la eliminación normal de BST
    if (raiz == NULL)
        return raiz;

    // Buscar el nodo a eliminar
    if (email < raiz->data.getEmail())
        raiz->Izq = eliminar(raiz->Izq, email);
    else if (email > raiz->data.getEmail())
        raiz->Der = eliminar(raiz->Der, email);
    else {
        // Caso 1: Nodo con solo un hijo o sin hijos
        if ((raiz->Izq == NULL) || (raiz->Der == NULL)) {
            Nodo temp = raiz->Izq ? raiz->Izq : raiz->Der;

            // Caso 0: Sin hijo
            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else // Caso 1: Un hijo
                *raiz = *temp; // Copiar el contenido del hijo no vacío

            delete temp;
        } else {
            // Caso 2: Nodo con dos hijos, obtener el sucesor en inorden (menor del subárbol derecho)
            Nodo temp = getMinValueNode(raiz->Der);

            // Copiar los datos del sucesor al nodo actual
            raiz->data = temp->data;

            // Eliminar el sucesor en inorden
            raiz->Der = eliminar(raiz->Der, temp->data.getEmail());
        }
    }

    // Si el árbol tenía solo un nodo, simplemente devolver
    if (raiz == NULL)
        return raiz;

    // Paso 2: Actualizar la altura del nodo actual
    raiz->altura = 1 + max(altura(raiz->Izq), altura(raiz->Der));

    // Paso 3: Obtener el factor de balance de este nodo
    int balance = getBalance(raiz);

    // Paso 4: Balancear el árbol
    // Rotación derecha si el nodo está desbalanceado a la izquierda
    if (balance > 1 && getBalance(raiz->Izq) >= 0)
        return rotacionDerecha(raiz);

    // Rotación izquierda-derecha
    if (balance > 1 && getBalance(raiz->Izq) < 0) {
        raiz->Izq = rotacionIzquierda(raiz->Izq);
        return rotacionDerecha(raiz);
    }

    // Rotación izquierda si el nodo está desbalanceado a la derecha
    if (balance < -1 && getBalance(raiz->Der) <= 0)
        return rotacionIzquierda(raiz);

    // Rotación derecha-izquierda
    if (balance < -1 && getBalance(raiz->Der) > 0) {
        raiz->Der = rotacionDerecha(raiz->Der);
        return rotacionIzquierda(raiz);
    }

    return raiz;
}

// Obtener el nodo con el valor mínimo en el subárbol
Nodo Avl::getMinValueNode(Nodo nodo) {
    Nodo actual = nodo;

    // Bucle para encontrar la hoja más a la izquierda
    while (actual->Izq != NULL)
        actual = actual->Izq;

    return actual;
}

// Método público para eliminar
void Avl::eliminar(string email) {
    Raiz = eliminar(Raiz, email);
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

void Avl::procesarRequest(Request* request) {
    std::string emisor = request->getEmisor();
    std::string receptor = request->getReceptor();
    std::string estado = request->getEstado();

    // Buscar los usuarios en el árbol AVL
    Nodo userReceptor = buscar(receptor);
    Nodo userEmisor = buscar(emisor);

    if (userReceptor == nullptr || userEmisor == nullptr) {
        qDebug() << "Uno de los usuarios no existe en el sistema.";
        return;
    }

    // Verificar el estado de la solicitud
    if (estado == "PENDIENTE") {
        // Agregar la solicitud a ambas partes
        userReceptor->data.addRequestReceived(*request);
        userEmisor->data.addRequestSent(*request);
        qDebug() << "Solicitud pendiente procesada entre " << emisor.c_str() << " y " << receptor.c_str();
    } else if (estado == "ACEPTADA") {
        // Agregar a la lista de amigos de ambos usuarios
        userReceptor->data.addFriend(emisor);
        userEmisor->data.addFriend(receptor);
        qDebug() << emisor.c_str() << " y " << receptor.c_str() << " ahora son amigos.";
    } else {
        qDebug() << "Estado de solicitud no válido.";
    }
}

void Avl::fillUsersTableWithOrden(QTableWidget *table, string orden) {
    fillUsersTableWithOrden(Raiz, table, orden);
}

void Avl::fillUsersTableWithOrden(Nodo &nodo, QTableWidget *table, string orden) {
    if (nodo != NULL) {
        // Preorden: procesar el nodo antes de los subárboles
        if(orden == "PreOrden") {
            agregarTabla(nodo, table);
            fillUsersTableWithOrden(nodo->Izq,table, orden);
            fillUsersTableWithOrden(nodo->Der,table, orden);
        }

        // Inorden: procesar el nodo entre los subárboles
        else if(orden == "InOrden") {
            fillUsersTableWithOrden(nodo->Izq,table, orden);
            agregarTabla(nodo, table);
            fillUsersTableWithOrden(nodo->Der,table, orden);
        }

        // Postorden: procesar el nodo después de los subárboles
        else if(orden == "PostOrden") {
            fillUsersTableWithOrden(nodo->Izq,table, orden);
            fillUsersTableWithOrden(nodo->Der,table, orden);
            agregarTabla(nodo, table);
        }
    }
}

void Avl::agregarTabla(Nodo &aux, QTableWidget *table) {
    int row = table->rowCount(); // Obtiene el número actual de filas
    table->insertRow(row); // Inserta una nueva fila al final de la tabla

    // Agrega los datos a cada celda de la fila
    table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(aux->data.getName())));
    table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(aux->data.getLastName())));
    table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(aux->data.getEmail())));
    table->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(aux->data.getBirthDate())));

    QPushButton* modifyBtn = new QPushButton("Modificar");
    QPushButton* deleteBtn = new QPushButton("Eliminar");

    QObject::connect(modifyBtn, &QPushButton::clicked, [table, row, &aux](){
        qDebug() << "Modificando usuario";
    });

    QObject::connect(deleteBtn, &QPushButton::clicked, [this, &aux](){
        this->eliminar(aux->data.getEmail());
        qDebug() << "Eliminando el usuario: " << aux->data.getEmail();
    });
    table->setCellWidget(row, 4, modifyBtn);
    table->setCellWidget(row, 5, deleteBtn);

}


