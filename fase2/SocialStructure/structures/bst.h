#ifndef BST_H
#define BST_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <iomanip>
#include "../models/post.h" // Incluir la clase Post
#include "../models/comment.h"
#include <QScrollArea>
#include <QVBoxLayout>
#include <QLabel>
using namespace std;

class Node
{
private:
    Post value; // Ahora almacenamos un Post
    Node *right, *left;
public:
    Node(Post value); // Constructor para Post
    Post& getValue();  // Devuelve el Post
    Node* getRight();
    Node* getLeft();

    void setValue(Post value); // Asigna un Post
    void setRight(Node *right);
    void setLeft(Node *left);
};

class BST
{
private:
    Node* root;

    Node* insert(Node* root, Post value);
    bool compareDates(string date1, string hour1, string date2, string hour2); // Nueva función para comparar fechas
    void preorder(Node *root);
    void deleteTree(Node* root);
    void graph(Node *root, ofstream &content);
public:
    BST();

    void insert(Post value); // Ahora inserta un Post
    void preorder();
    void deleteTree();
    void graph();
    void fillScrollAreaWithPosts(QScrollArea *scrollArea);
    void fillScrollAreaWithPosts(Node *node, QVBoxLayout *layout);
    Node *search(Node* root, Post postToFind);
    void insertComment(Post postToFind, Comment commentToInsert);
    ~BST();
};

#endif // BST_H
