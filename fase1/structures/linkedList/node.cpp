#include "./headers/node.h"
#include "../../models/headers/User.h"
#include <iostream>
using namespace std;

Node::Node()
{
    this->next = NULL;
}

Node::Node(User user)
{
    this->user = user;
    this->next = NULL;
}

void Node::printNode()
{
    cout << "Nombre: " << this->user.getName() << endl;
    cout << "Apellido: " << this->user.getLastName() << endl;
    cout << "Fecha de nacimiento: " << this->user.getBirthDate() << endl;
    cout << "Correo: " << this->user.getEmail() << endl;
    cout << "Contrasena: " << this->user.getPassword() << endl;
}