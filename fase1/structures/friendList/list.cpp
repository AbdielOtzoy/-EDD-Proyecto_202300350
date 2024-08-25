#include <iostream>
#include <string>
#include "./list.h"

using namespace std;

NodeFriend::NodeFriend()
{
    this->name = "";
    this->next = nullptr;
}

NodeFriend::NodeFriend(string name)
{
    this->name = name;
    this->next = nullptr;
}

void NodeFriend::printNodeFriend()
{
    cout << this->name << endl;
}

FriendList::FriendList()
{
    this->head = nullptr;
}

void FriendList::insert(string name)
{
    NodeFriend *newNodeFriend = new NodeFriend(name);
    if (this->head == nullptr)
    {
        this->head = newNodeFriend;
    }
    else
    {
        NodeFriend *current = this->head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = newNodeFriend;
    }
}

void FriendList::printFriendList()
{
    NodeFriend *current = this->head;
    while (current != nullptr)
    {
        current->printNodeFriend();
        current = current->next;
    }
}

int FriendList::getSize()
{
    NodeFriend *current = this->head;
    int size = 0;
    while (current != nullptr)
    {
        size++;
        current = current->next;
    }
    return size;
}

string FriendList::get(int index)
{
    NodeFriend *current = this->head;
    int i = 0;
    while (current != nullptr)
    {
        if (i == index)
        {
            return current->name;
        }
        i++;
        current = current->next;
    }
    return "";
}
