#include <iostream>
#include <string>
#include "../models/headers/Post.h"

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

string Post::getAuthor()
{
    return this->author;
}

string Post::getContent()
{
    return this->content;
}

string Post::getDate()
{
    return this->date;
}

string Post::getTime()
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
    cout << "Autor: " << this->author << endl;
    cout << "Contenido: " << this->content << endl;
    cout << "Fecha: " << this->date << endl;
    cout << "Hora: " << this->time << endl;
}
