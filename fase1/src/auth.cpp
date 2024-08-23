#include <iostream>
#include "./headers/auth.h"
#include "../models/headers/User.h"
#include "../structures/linkedList/headers/list.h"
using namespace std;

// Definición de las variables globales
bool isLogged = false;
bool isAdmin = false;
User loggedUser;

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

    // establecer usuario como logeado
    isLogged = true;
    loggedUser = user;
}

// implementacion de la funcion loginUser
void loginUser()
{
    string email, password;
    cout << "Correo: ";
    cin >> email;
    cout << "Contrasena: ";
    cin >> password;

    if (email == "admin" && password == "admin")
    {
        cout << "¡Bienvenido administrador!" << endl;
        isLogged = true;
        isAdmin = true;
        return;
    }
    Node *user = list.search(email);
    if (user != NULL)
    {
        if (user->user.getPassword() == password)
        {
            cout << "¡Bienvenido " << user->user.getName() << "!" << endl;
            isLogged = true;
            loggedUser = user->user;
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

// implementacion de la funcion logoutUser
void logoutUser()
{
    isLogged = false;
    loggedUser = User();
    cout << "¡Sesion cerrada!" << endl;
}