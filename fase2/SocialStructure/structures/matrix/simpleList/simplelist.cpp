#include "simplelist.h"

SimpleList::SimpleList(int typeHeader)
{
    this->typeHeader = typeHeader;
    size = 0;
    head = nullptr;
    tail = nullptr;
}

/* Inserting a new node if not exist, else
   just return the pointer of that node
*/
ListNode *SimpleList::insert(string name)
{
    ListNode *newNode = new ListNode(name);
    ListNode *current = head;
    ListNode *previous = nullptr;

    // Check if the list is empty
    if (current == nullptr)
    {
        head = newNode;
        tail = newNode;
        size++;
        return newNode;
    }

    // Traverse the list
    do
    {
        if (current->name == name)
        {
            delete newNode;
            return current;
        }
        else if (current->name > name)
        {
            if (previous == nullptr)
            {
                newNode->next = head;
                head = newNode;
            }
            else
            {
                previous->next = newNode;
                newNode->next = current;
            }
            size++;
            return newNode;
        }
        previous = current;
        current = current->next;
    } while (current != nullptr);

    // Insert at the end
    tail->next = newNode;
    tail = newNode;
    size++;
    return newNode;
}

void SimpleList::print()
{
    ListNode *current = head;

    // Check for empty list
    if (current == nullptr)
    {
        cout << "Your list is empty" << endl;
    }
    else
    {
        // Traverse the list
        do
        {
            cout << current->name << endl;
            current = current->next;
        } while (current != nullptr);
    }
}

SimpleList::~SimpleList()
{
    ListNode *current = head;
    ListNode *next = nullptr;
    int rowHeader = 0;

    /* When typeHeader is 0(row header) i'm goin to delete
    the header nodes and the matrix nodes, else
    if type header is 1(col header) i'm goint to delete
    just the header nodes
  */
    if (typeHeader == rowHeader)
    {
        while (current != nullptr)
        {
            MatrixNode *currentMatrixNode = current->access;
            MatrixNode *nextMatrixNode = nullptr;
            while (currentMatrixNode != nullptr)
            {
                nextMatrixNode = currentMatrixNode->right;
                delete currentMatrixNode;
                currentMatrixNode = nextMatrixNode;
            }
            next = current->next;
            delete current;
            current = next;
        }
    }
    else
    {
        while (current != nullptr)
        {
            next = current->next;
            delete current;
            current = next;
        }
    }
}
