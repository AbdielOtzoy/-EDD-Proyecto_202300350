#include "./headers/node.h"
#include <iostream>
#include "../../models/headers/Post.h"

using namespace std;

NodeDoubly::NodeDoubly()
{
    this->post = Post();
    this->next = NULL;
    this->prev = NULL;
}

NodeDoubly::NodeDoubly(Post post)
{
    this->post = post;
    this->next = NULL;
    this->prev = NULL;
}

void NodeDoubly::printNodeDoubly()
{
    this->post.printPost();
}
