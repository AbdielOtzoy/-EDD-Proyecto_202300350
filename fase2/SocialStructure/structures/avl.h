#ifndef AVL_H
#define AVL_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <QTableWidget>
#include <QPushButton>
#include "../user.h"

using namespace std;

struct nodo
{
    User data; // Ahora almacenamos un objeto User
    nodo *Izq;
    nodo *Der;
};

typedef struct nodo *Nodo;

class
Avl
{
public:

    Avl();
    void ver();
    void agregar(User user);
    void elimina();
    Nodo buscar(string email);
    int contar();
    Nodo getRaiz();
    int nodoN(Nodo, int);
    Nodo buscar(Nodo &, string email);
    int canNivel(Nodo);
    void verNivel(Nodo, int);
    int numNoN(Nodo, int);
    int sumatoria(Nodo);
    void graficarDot();
    void graficarDot(Nodo, stringstream &);

    void agregarUsuariosATabla(QTableWidget *table, User *userLogged);
    void agregarUsuariosATabla(Nodo &, QTableWidget *table, User *userLogged);

    virtual ~
        Avl();

private:
    int contar(Nodo &);
    void elimina(Nodo &);
    void inOrden(Nodo &);
    Nodo agregar(Nodo &, User user);
    Nodo Raiz;

    // Función de comparación de strings
    bool compararStrings(string str1, string str2);
};

#endif // AVL_H
