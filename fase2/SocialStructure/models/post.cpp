#include "post.h"
#include <iostream>
#include <string>
#include <QDebug>

using namespace std;

Post::Post()
{
    this->author = "";
    this->content = "";
    this->date = "";
    this->time = "";
}

Post::Post(string author, string content, string date, string time)
{
    this->author = author;
    this->content = content;
    this->date = date;
    this->time = time;
}

// Asegúrate de que los métodos sean constantes
string Post::getAuthor() const
{
    return this->author;
}

string Post::getContent() const
{
    return this->content;
}

string Post::getDate() const
{
    return this->date;
}

string Post::getTime() const
{
    return this->time;
}

void Post::setAuthor(string author)
{
    this->author = author;
}

void Post::setContent(string content)
{
    this->content = content;
}

void Post::setDate(string date)
{
    this->date = date;
}

void Post::setTime(string time)
{
    this->time = time;
}

void Post::printPost()
{
    qDebug() << "Autor: " << this->author;
    qDebug() << "Contenido: " << this->content;
    qDebug() << "Fecha: " << this->date;
    qDebug() << "Hora: " << this->time;
}



