#ifndef REQUEST_H
#define REQUEST_H

#include <string>

using namespace std;

class Request
{
private:
    string emisor;
    string receptor;
    string estado;

public:
    Request();
    Request(string emisor, string receptor, string estado);
    string getEmisor();
    string getReceptor();
    string getEstado();
    void setEmisor(string);
    void setReceptor(string);
    void setEstado(string);

    void printRequest();
};
#endif // REQUEST_H
