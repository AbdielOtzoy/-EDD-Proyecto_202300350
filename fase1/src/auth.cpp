#include <iostream>
#include "./headers/auth.h"
#include "../models/headers/User.h"
#include "../structures/linkedList/headers/list.h"
using namespace std;

LinkedList list;
// implementacion de la funcion registerUser
void registerUser()
{
    string name, lastName, birthDate, email, password;
    cout << "Nombre: ";
    cin >> name;
    cout << "Apellido: ";
    cin >> lastName;
    cout << "Fecha de nacimiento: ";
    cin >> birthDate;
    cout << "Correo: ";
    cin >> email;
    cout << "Contrasena: ";
    cin >> password;

    User user(name, lastName, birthDate, email, password);
    cout << "¡Usuario registrado exitosamente!" << endl;

    // insertar usuario en la lista
    list.insert(user);
    list.printList();
}

// implementacion de la funcion loginUser
void loginUser()
{
    string email, password;
    cout << "Correo: ";
    cin >> email;
    cout << "Contrasena: ";
    cin >> password;

    Node *user = list.search(email);
    if (user != NULL)
    {
        if (user->user.getPassword() == password)
        {
            cout << "¡Bienvenido " << user->user.getName() << "!" << endl;
        }
        else
        {
            cout << "Contrasena incorrecta" << endl;
        }
    }
    else
    {
        cout << "Usuario no encontrado" << endl;
    }
}