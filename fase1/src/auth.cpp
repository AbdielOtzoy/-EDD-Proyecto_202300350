#include <iostream>
#include "./headers/auth.h"
#include "../structures/linkedList/headers/list.h"
using namespace std;

// Definición de las variables globales
bool isLogged = false;
bool isAdmin = false;
User loggedUser;

LinkedList list;

// Función para agregar usuarios de prueba
void addTestUsers()
{
    // Crear usuarios de prueba
    User user1("John", "Doe", "01-01-1990", "john", "123");
    User user2("Jane", "Smith", "02-02-1992", "jane", "123");
    User user3("Bob", "Johnson", "03-03-1995", "bob", "123");

    // Insertar usuarios en la lista
    list.insert(user1);
    list.insert(user2);
    list.insert(user3);
}

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
    isAdmin = false;
    loggedUser = User();
    cout << "¡Sesion cerrada!" << endl;
}
