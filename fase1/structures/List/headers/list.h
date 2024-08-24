#ifndef LIST_H
#define LIST_H

#include "./node.h"
#include "../../../models/headers/Request.h"
#include <string>

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
};

#endif
