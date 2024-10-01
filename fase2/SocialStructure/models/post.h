#ifndef POST_H
#define POST_H

#include <iostream>
#include "../structures/btree.h";
#include "comment.h"

using namespace std;

class Post
{
private:
    string author;
    string content;
    string date;
    string time;

public:
    Post();
    BTree comments;
    Post(string author, string content, string date, string time);

    // Cambiar las siguientes líneas para que los métodos sean constantes
    string getAuthor() const; // Método constante
    string getContent() const; // Método constante
    string getDate() const; // Método constante
    string getTime() const; // Método constante

    void setAuthor(string author);
    void setContent(string content);
    void setDate(string date);
    void setTime(string time);

    void printPost();
};

#endif // POST_H
