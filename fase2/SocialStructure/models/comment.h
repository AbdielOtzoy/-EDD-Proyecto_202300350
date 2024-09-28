#ifndef COMMENT_H
#define COMMENT_H

#include <string>
using namespace std;

class Comment
{
private:
    string author;
    string content;
    string date;
    string time;

public:
    // Constructores
    Comment();
    Comment(string author, string content, string date, string time);

    // Métodos de acceso marcados como const
    string getAuthor() const;
    string getContent() const;
    string getDate() const;
    string getTime() const;

    // Métodos de modificación
    void setAuthor(string author);
    void setContent(string content);
    void setDate(string date);
    void setTime(string time);

    // Método para imprimir el comentario
    void printComment() const;
};

#endif // COMMENT_H
