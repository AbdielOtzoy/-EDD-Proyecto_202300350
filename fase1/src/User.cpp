#include "../models/headers/User.h"
#include <iostream>
#include <string>

using namespace std;

// implementacion del constructor por defecto
User::User()
{
    name = "";
    lastName = "";
    birthDate = "";
    email = "";
    password = "";
}

// implementacion del constructor con parametros
User::User(string name, string lastName, string birthDate, string email, string password)
{
    this->name = name;
    this->lastName = lastName;
    this->birthDate = birthDate;
    this->email = email;
    this->password = password;
}

// implementacion de los metodos get
string User::getName()
{
    return name;
}

string User::getLastName()
{
    return lastName;
}

string User::getBirthDate()
{
    return birthDate;
}

string User::getEmail()
{
    return email;
}

string User::getPassword()
{
    return password;
}

// implementacion de los metodos set
void User::setName(string name)
{
    this->name = name;
}

void User::setLastName(string lastName)
{
    this->lastName = lastName;
}

void User::setBirthDate(string birthDate)
{
    this->birthDate = birthDate;
}

void User::setEmail(string email)
{
    this->email = email;
}

void User::setPassword(string password)
{
    this->password = password;
}

// implementacion del metodo printUser
void User::printUser()
{
    cout << "Nombre: " << name << endl;
    cout << "Apellido: " << lastName << endl;
    cout << "Fecha de nacimiento: " << birthDate << endl;
    cout << "Correo: " << email << endl;
    cout << "Contrasena: " << password << endl;
}

// implementacion del metodo addRequestSent
void User::addRequestSent(Request request)
{
    requestsSent.insert(request);
}

// implementacion del metodo addRequestReceived
void User::addRequestReceived(Request request)
{
    requestsReceived.push(request);
}

// implementacion del metodo printRequestsSent
void User::printRequestsSent()
{
    requestsSent.printList();
}

// implementacion del metodo printRequestsReceived
void User::printRequestsReceived()
{
    // mostrar solamente la solicitud que esta en el tope
    requestsReceived.peek().printRequest();
}

// implementacion del metodo removeRequestSent
void User::removeRequestSent(Request request)
{
    requestsSent.remove(request.getEmisor(), request.getReceptor());
}

// implementacion del metodo removeRequestReceived
void User::removeRequestReceived()
{
    requestsReceived.pop();
}

// implementacion del metodo addFriend
void User::addFriend(string name)
{
    friends.insert(name);
}

// implementacion del metodo printFriends
void User::printFriends()
{
    friends.printFriendList();
}

// implementacion del metodo getSizeFriends
int User::getSizeFriends()
{
    return friends.getSize();
}