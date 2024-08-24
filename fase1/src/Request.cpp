#include <iostream>
#include <string>
#include "../models/headers/Request.h"

using namespace std;

Request::Request()
{
    this->emisor = "";
    this->receptor = "";
    this->estado = "";
}

Request::Request(string emisor, string receptor, string estado)
{
    this->emisor = emisor;
    this->receptor = receptor;
    this->estado = estado;
}

string Request::getEmisor()
{
    return this->emisor;
}

string Request::getReceptor()
{
    return this->receptor;
}

string Request::getEstado()
{
    return this->estado;
}

void Request::setEmisor(string emisor)
{
    this->emisor = emisor;
}

void Request::setReceptor(string receptor)
{
    this->receptor = receptor;
}

void Request::setEstado(string estado)
{
    this->estado = estado;
}

void Request::printRequest()
{
    cout << "Emisor: " << this->emisor << endl;
    cout << "Receptor: " << this->receptor << endl;
    cout << "Estado: " << this->estado << endl;
}
