#ifndef POST_H
#define POST_H

#include <iostream>
#include "../structures/btree.h";
#include "comment.h"

using namespace std;

class Post
{
private:
    string author;
    string content;
    string date;
    string time;

public:
    Post();
    BTree comments;
    Post(string author, string content, string date, string time);
    string getAuthor();
    string getContent();
    string getDate();
    string getTime();
    void setAuthor(string author);
    void setContent(string content);
    void setDate(string date);
    void setTime(string time);
    void printPost();
};

#endif // POST_H
