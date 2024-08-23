#include "./node.h"
#include "../../../models/headers/User.h"

class LinkedList
{
private:
    Node *head;
    int size;

public:
    LinkedList();
    void insert(User user);
    void printList();
    void remove(string email);
    Node *search(string email);
    int getSize();
};
