#define FriendList_H

#include <iostream>
#include <string>

using namespace std;

class NodeFriend
{
private:
public:
    string name;
    NodeFriend *next;

    NodeFriend();
    NodeFriend(string name);
    void printNodeFriend();
};

class FriendList
{
private:
public:
    NodeFriend *head;

    FriendList();
    void insert(string name);
    void printFriendList();
    int getSize();
    string get(int index);
};
