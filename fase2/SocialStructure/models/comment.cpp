#include "comment.h"
#include <QDebug>
#include <string>

using namespace std;

Comment::Comment()
{
    author = "";
    content = "";
    date = "";
    time = "";
}

Comment::Comment(string author, string content, string date, string time)
{
    this->author = author;
    this->content = content;
    this->date = date;
    this->time = time;
}

// Métodos de acceso marcados como const
string Comment::getAuthor() const
{
    return author;
}

string Comment::getContent() const
{
    return content;
}

string Comment::getDate() const
{
    return date;
}

string Comment::getTime() const
{
    return time;
}

void Comment::setAuthor(string author)
{
    this->author = author;
}

void Comment::setContent(string content)
{
    this->content = content;
}

void Comment::setDate(string date)
{
    this->date = date;
}

void Comment::setTime(string time)
{
    this->time = time;
}

void Comment::printComment() const
{
    qDebug() << "Author: " << author;
    qDebug() << "Content: " << content;
    qDebug() << "Date: " << date;
    qDebug() << "Time: " << time;
}

