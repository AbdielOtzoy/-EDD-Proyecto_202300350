#define NODE_H

#include "../../../models/headers/Request.h"
class NodeList
{
private:
public:
    Request request;
    NodeList *next;

    NodeList();
    NodeList(Request request);

    void printNode();
};
