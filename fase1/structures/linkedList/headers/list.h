#include "./node.h"
#include "../../../models/headers/User.h"

class LinkedList
{
private:
    int size;

public:
    Node *head;
    LinkedList();
    void insert(User user);
    void printList();
    void remove(string email);
    Node *search(string email);
    int getSize();
};
