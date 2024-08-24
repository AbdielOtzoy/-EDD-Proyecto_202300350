#include <iostream>
#include "./headers/auth.h"
#include "../structures/linkedList/headers/list.h"
#include "../structures/doublyList/headers/list.h"
#include "../models/headers/User.h"
#include "../models/headers/Request.h"
#include "../models/headers/Post.h"
#include <ctime>
using namespace std;

// Definición de las variables globales
bool isLogged = false;
bool isAdmin = false;
User loggedUser;

// lista simple enlazada para almacenar los usuarios
LinkedList list;

// lista doblemente enlazada para almacenar todos los posts
DoublyList posts;

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

// implementacion de la funcion sendRequest
void sendRequest()
{
    string email;
    cout << "Correo del destinatario: ";
    cin >> email;

    Node *receiver = list.search(email);
    if (receiver != NULL)
    {
        Request request(loggedUser.getEmail(), receiver->user.getEmail(), "pending"); // Assuming the Request class has a constructor that accepts three arguments: sender email, receiver email, and status
        receiver->user.addRequestReceived(request);
        loggedUser.addRequestSent(request);
        cout << "¡Solicitud enviada!" << endl;
    }
    else
    {
        cout << "Usuario no encontrado" << endl;
    }
}

// implementacion de la funcion respondRequest
void respondRequest()
{
    // mostrar solicitudes recibidas
    loggedUser.printRequestsReceived();

    // responder solicitud, como es una pila se responde la solicitud que esta en el tope
    if (!loggedUser.requestsReceived.isEmpty())
    {
        Request request = loggedUser.requestsReceived.peek();
        cout << "1. Aceptar" << endl;
        cout << "2. Rechazar" << endl;
        cout << "Opcion: ";
        int opcion;
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            request.setEstado("accepted");
            cout << "¡Solicitud aceptada!" << endl;
            break;
        case 2:
            request.setEstado("rejected");
            cout << "¡Solicitud rechazada!" << endl;
            break;
        default:
            cout << "Opcion no valida" << endl;
        }

        // eliminar solicitud de la pila
        loggedUser.removeRequestReceived();

        // actualizar solicitud en la lista del emisor
        Node *sender = list.search(request.getEmisor());
        sender->user.removeRequestSent(request);
    }
    else
    {
        cout << "No hay solicitudes pendientes" << endl;
    }
}

// implementacion de la funcion createPost
void createPost()
{
    // pedir contenido de la publicacion
    // tener en cuenta que el contenido puede ser una cadena con espacios
    string content;
    cout << "Contenido: ";
    cin.ignore();
    getline(cin, content);

    // obtener la fecha y hora actual
    time_t now = time(0);
    tm *ltm = localtime(&now);
    string date = to_string(1 + ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year);
    string time = to_string(1 + ltm->tm_hour) + ":" + to_string(1 + ltm->tm_min) + ":" + to_string(1 + ltm->tm_sec);

    Post post(loggedUser.getEmail(), content, date, time);
    posts.addNode(post);
    cout << "¡Publicacion creada!" << endl;

    // mostrar la publicacion creada
    posts.printList();
}