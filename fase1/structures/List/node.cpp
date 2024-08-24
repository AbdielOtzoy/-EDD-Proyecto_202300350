#include "./headers/node.h"
#include "../../models/headers/Request.h"
#include <iostream>
using namespace std;

NodeList::NodeList()
{
    this->next = NULL;
}

NodeList::NodeList(Request request)
{
    this->request = request;
    this->next = NULL;
}

void NodeList::printNode()
{
    cout << "Emisor: " << this->request.getEmisor() << endl;
    cout << "Receptor: " << this->request.getReceptor() << endl;
    cout << "Estado: " << this->request.getEstado() << endl;
    cout << "--------------------------------" << endl;
}
