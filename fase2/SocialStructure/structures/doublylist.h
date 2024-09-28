#ifndef DOUBLYLIST_H
#define DOUBLYLIST_H
#include "../models/post.h"
#include "friendlist.h"
#include "bst.h"
#include "../models/comment.h"

using namespace std;

class NodeDoubly
{
private:
public:
    NodeDoubly();
    NodeDoubly(Post post);
    Post post;
    NodeDoubly *next;
    NodeDoubly *prev;
    void printNodeDoubly();
};

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
    void createDotFile();
    void topFiveUsersWithMostPosts();
    void fillBstPosts(FriendList &friends, string userlogged, BST &bst);
    bool isFriend(FriendList &friends, string author);
    void insertCommentByContent(string contentToFind, Comment commentToInsert);
};

#endif // DOUBLYLIST_H
