#define NODE_H

#include <iostream>
#include "../../../models/headers/Post.h"

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