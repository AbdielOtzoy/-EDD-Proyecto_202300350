#ifndef LIST_H
#define LIST_H

#include "../models/request.h"
#include <QTableWidget>
class User;

class NodeList
{
private:
public:
    Request request;
    NodeList *next;

    NodeList();
    NodeList(Request request);

    void printNode();
};

class List
{
private:
    NodeList *head;
    int size;

public:
    List();
    void insert(Request request);
    void printList();
    void remove(std::string emisor, std::string receptor);
    int getSize();
    NodeList *search(std::string email);
    void agregarSolicitudTabla(QTableWidget *table,User *user);
    void createDotFile();
    bool isEmpty();
};

#endif // LIST_H
