#include "./node.h"
#include <iostream>

using namespace std;

class DoublyList
{
private:
public:
    DoublyList();
    NodeDoubly *head;
    NodeDoubly *tail;
    void addNode(Post post);
    void printList();
    void deleteNode(string author);
    void searchNode(string author);
};