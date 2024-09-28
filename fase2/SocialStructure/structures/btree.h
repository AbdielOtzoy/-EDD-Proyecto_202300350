#ifndef BTREE_H
#define BTREE_H

#define degree 5
#include <iostream>
#include <fstream>
#include <sstream>
#include "../models/comment.h"
#include <QVBoxLayout>

using namespace std;

class Page
{
private:
    /* data */

public:
    Page(/* args */);
    bool fullPage();
    Comment keys[degree]; // Ahora las claves son objetos de tipo Comment
    Page *branches[degree];
    int count;
};

class BTree
{
private:
    Page *root;
    void insert(Page **root, Comment key); // Cambiar int por Comment
    void push(Page *actualPage, Comment key, bool &goUp, Comment &median, Page **newPage);
    bool searchNodeOnPage(Page *current, Comment value, int &k);
    void split(Page *current, Comment key, Page *rd, int k, Comment &median, Page **newPage);
    void pushNode(Page *current, Comment key, Page *rd, int k);
    void getContent(Page *current, stringstream &accum, int &countNode, int &countAux, stringstream &accumLink);
    void write_dot(string code);

public:
    BTree(/* args */);
    void graph();
    void insert(Comment key); // Cambiar int por Comment
    bool isEmpty();
    void printTree();
    void printTree(Page *current);
    void fillLayoutWithComments(QVBoxLayout *layout);
    void fillLayoutWithComments(Page *currentPage, QVBoxLayout *layout);
};

#endif // BTREE_H
