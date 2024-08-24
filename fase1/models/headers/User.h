#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include "../../structures/List/headers/list.h"
#include "../../structures/Stack/Stack.h"
#include "../../models/headers/Request.h"

using namespace std;

class User
{
private:
    string name;
    string lastName;
    string birthDate;
    string email;
    string password;

public:
    List requestsSent;
    Stack requestsReceived;
    User();
    User(string name, string lastName, string birthDate, string email, string password);
    string getName();
    string getLastName();
    string getBirthDate();
    string getEmail();
    string getPassword();
    void setName(string name);
    void setLastName(string lastName);
    void setBirthDate(string birthDate);
    void setEmail(string email);
    void setPassword(string password);

    void addRequestSent(Request request);
    void addRequestReceived(Request request);
    void printRequestsSent();
    void printRequestsReceived();
    void removeRequestSent(Request request);
    void removeRequestReceived();

    void printUser();
};

#endif