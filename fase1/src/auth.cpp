#include <iostream>
#include "./headers/auth.h"
#include "../structures/linkedList/headers/list.h"
#include "../structures/doublyList/headers/list.h"
#include "../models/headers/User.h"
#include "../models/headers/Request.h"
#include "../models/headers/Post.h"
#include "../structures/matrix/matrix/headers/matrix.h"
#include "../structures/doublyCircleList/list.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <ctime>
using namespace std;

// Definición de las variables globales
bool isLogged = false;
bool isAdmin = false;
User loggedUser;

using json = nlohmann::json;

// lista simple enlazada para almacenar los usuarios
LinkedList list;

// lista doblemente enlazada para almacenar todos los posts
DoublyList posts;

// matriz para almacenar las relaciones de amistad
Matrix matrixRelation;

// lista circular doblemente enlazada para almacenar temporalmente las publicaciones del usuario logeado y sus amigos
DoublyCircleList availablePosts;

// Función para agregar usuarios de prueba
void addTestData()
{
    // Crear usuarios de prueba
    User user1("John", "Doe", "01-01-1990", "john", "123");
    User user2("Jane", "Smith", "02-02-1992", "jane", "123");
    User user3("Bob", "Johnson", "03-03-1995", "bob", "123");
    User user4("Alice", "Williams", "04-04-1998", "alice", "123");
    User user5("Eve", "Brown", "05-05-2000", "eve", "123");

    // Crear solicitudes de amistad
    Request request1("john", "jane", "PENDIENTE");
    Request request2("john", "bob", "PENDIENTE");
    Request request3("bob", "jane", "PENDIENTE");
    Request request4("alice", "jane", "PENDIENTE");

    // Agregar solicitudes a los usuarios
    user1.addRequestSent(request1);
    user1.addRequestSent(request2);
    user2.addRequestReceived(request1);
    user3.addRequestReceived(request2);
    user3.addRequestSent(request3);
    user2.addRequestReceived(request3);
    user4.addRequestSent(request4);
    user2.addRequestReceived(request4);

    // Insertar usuarios en la lista
    list.insert(user1);
    list.insert(user2);
    list.insert(user3);
    list.insert(user4);
    list.insert(user5);
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

// implementacion de la funcion deleteUser
void deleteUser()
{
    // si es administrador, eliminar usuario por correo
    if (isAdmin)
    {
        string email;
        cout << "Correo del usuario a eliminar: ";
        cin >> email;
        list.remove(email);
        cout << "¡Usuario eliminado!" << endl;
    }
    else
    {
        // si es usuario, eliminar cuenta
        deleteAccount();
    }
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
    // eliminar publicaciones disponibles, si las hay
    if (!availablePosts.isEmpty())
    {
        availablePosts.clear();
    }
    cout << "¡Sesion cerrada!" << endl;
}

// implementacion de la funcion logoutAdmin
void logoutAdmin()
{
    isLogged = false;
    isAdmin = false;
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
        Request request(loggedUser.getEmail(), receiver->user.getEmail(), "pending");
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
    // responder solicitud, como es una pila se responde la solicitud que esta en el tope
    if (!loggedUser.requestsReceived.isEmpty())
    {
        // mostrar solicitudes recibidas
        loggedUser.printRequestsReceived();
        Request request = loggedUser.requestsReceived.peek();
        cout << "1. Aceptar" << endl;
        cout << "2. Rechazar" << endl;
        cout << "Opcion: ";
        int opcion;
        cin >> opcion;

        Node *sender = list.search(request.getEmisor());
        switch (opcion)
        {
        case 1:
            request.setEstado("accepted");
            cout << "¡Solicitud aceptada!" << endl;
            // agregar a la matriz de relaciones
            matrixRelation.insert(loggedUser.getName(), sender->user.getName(), 1);

            // agregar a la lista de amigos de ambos usuarios
            loggedUser.addFriend(sender->user.getEmail());
            sender->user.addFriend(loggedUser.getEmail());
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

// implementacion de la funcion viewProfile
void viewProfile()
{
    // mostrar perfil del usuario logeado
    loggedUser.printUser();
}

// implementacion de la funcion viewMyFriends
void viewMyFriends()
{
    // mostrar lista de amigos del usuario logeado
    loggedUser.printFriends();
}

// implementacion de la funcion viewAvailablePosts, se muestran todas las publicaciones de los amigos del usuario logeado y las publicaciones del usuario logeado
void viewAvailablePosts()
{
    // agregar las publicaciones del usuario logeado a la lista de publicaciones disponibles
    posts.filterByAuthor(loggedUser.getEmail(), availablePosts);

    // agregar las publicaciones de los amigos del usuario logeado a la lista de publicaciones disponibles
    for (int i = 0; i < loggedUser.friends.getSize(); i++)
    {
        string friendEmail = loggedUser.friends.get(i);
        posts.filterByAuthor(friendEmail, availablePosts);
    }

    // mostrar publicaciones disponibles, si la lista esta vacia mostrar un mensaje
    if (!availablePosts.isEmpty())
    {
        availablePosts.printList();
    }
    else
    {
        cout << "No hay publicaciones disponibles" << endl;
    }
}

// implementacion de la funcion deleteAccount
void deleteAccount()
{
    // eliminar usuario de la lista
    list.remove(loggedUser.getEmail());
    isLogged = false;
    isAdmin = false;
    loggedUser = User();
    cout << "¡Cuenta eliminada!" << endl;
}

// implementacion de la funcion loadUsers
void loadUsers()
{
    std::ifstream file("src/usuarios.json");
    if (!file.is_open())
    {
        std::cerr << "Error opening file" << std::endl;
    }

    json usuarios;
    try
    {
        usuarios = json::parse(file);
    }
    catch (const json::parse_error &e)
    {
        std::cerr << "JSON parsing error: " << e.what() << std::endl;
    }

    for (const auto &usuario : usuarios)
    {
        // Crear usuarios de prueba
        User user(usuario["nombres"], usuario["apellidos"], usuario["fecha_de_nacimiento"], usuario["correo"], usuario["contraseña"]);
        list.insert(user);
    }
}

// implementacion de la funcion loadRequests
void loadRequests()
{
    std::ifstream file("src/solicitudes.json");
    if (!file.is_open())
    {
        std::cerr << "Error opening file" << std::endl;
    }

    json solicitudes;
    try
    {
        solicitudes = json::parse(file);
    }
    catch (const json::parse_error &e)
    {
        std::cerr << "JSON parsing error: " << e.what() << std::endl;
    }

    for (const auto &solicitud : solicitudes)
    {
        // si el estado de la solicitud es pendiente, agregarla a la lista de solicitudes del usuario receptor y emisor
        // si el estado de la solicitud es aceptado, agregar a la matriz de relaciones y a la lista de amigos de ambos usuarios

        string emisor = solicitud["emisor"];
        string receptor = solicitud["receptor"];
        string estado = solicitud["estado"];

        // mostrar por consola las solicitudes cargadas
        cout << "Emisor: " << emisor << endl;
        cout << "Receptor: " << receptor << endl;
        cout << "Estado: " << estado << endl;

        if (estado == "PENDIENTE")
        {
            Node *receiver = list.search(receptor);
            Node *sender = list.search(emisor);
            Request request(emisor, receptor, estado);
            receiver->user.addRequestReceived(request);
            sender->user.addRequestSent(request);
        }
        else if (estado == "ACEPTADA")
        {

            // agregar a la lista de amigos de ambos usuarios
            Node *user1 = list.search(emisor);
            Node *user2 = list.search(receptor);

            // agregar a la matriz de relaciones, los nombres de los usuarios
            matrixRelation.insert(user1->user.getName(), user2->user.getName(), 1);
            user1->user.addFriend(receptor);
            user2->user.addFriend(emisor);
        }
    }
}

// implementacion de la funcion loadPosts
void loadPosts()
{
    std::ifstream file("src/publicaciones.json");
    if (!file.is_open())
    {
        std::cerr << "Error opening file" << std::endl;
    }

    json publicaciones;
    try
    {
        publicaciones = json::parse(file);
    }
    catch (const json::parse_error &e)
    {
        std::cerr << "JSON parsing error: " << e.what() << std::endl;
    }

    for (const auto &publicacion : publicaciones)
    {
        // Crear publicaciones de prueba
        Post post(publicacion["correo"], publicacion["contenido"], publicacion["fecha"], publicacion["hora"]);
        posts.addNode(post);

        // mostrar por consola las publicaciones cargadas
        post.printPost();
    }
}

// implementacion de la funcion viewUsers
void viewUsers()
{
    // generar archivo .dot con la lista de usuarios
    list.createDotFile();
}

// implementacion de la funcion viewMatrix
void viewMatrix()
{
    // generar archivo .dot con la matriz de relaciones
    matrixRelation.create_dot();
}

// implementacion de la funcion viewPosts
void viewPosts()
{
    // generar archivo .dot con la lista de publicaciones
    posts.createDotFile();
}

// implementacion de la funcion viewTopFiveUsersWithMostPosts
void viewTopFiveUsersWithMostPosts()
{
    // obtener los 5 usuarios con mas publicaciones
    posts.topFiveUsersWithMostPosts();
}

// implementacion de la funcion viewTopFiveUsersWithLeastFriends
void viewTopFiveUsersWithLeastFriends()
{
    // obtener los 5 usuarios con menos amigos
    list.topFiveUsersWithLeastFriends();
}

// implementacion de la funcion viewSentRequests
void viewSentRequests()
{
    // mostrar solicitudes enviadas
    if (!loggedUser.requestsSent.isEmpty())
    {
        loggedUser.requestsSent.createDotFile();
    }
    else
    {
        cout << "No hay solicitudes enviadas" << endl;
    }
}

// implementacion de la funcion viewReceivedRequests
void viewReceivedRequests()
{
    // mostrar solicitudes recibidas
    if (!loggedUser.requestsReceived.isEmpty())
    {
        loggedUser.requestsReceived.createDotFile();
    }
    else
    {
        cout << "No hay solicitudes pendientes" << endl;
    }
}

// implementacion de la funcion viewAvailablePostsDotFile
void viewAvailablePostsDotFile()
{
    if (!availablePosts.isEmpty())
    {
        availablePosts.createDotFile();
    }
    else
    {
        cout << "No hay publicaciones disponibles" << endl;
    }
}