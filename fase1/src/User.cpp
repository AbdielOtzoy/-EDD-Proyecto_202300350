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
