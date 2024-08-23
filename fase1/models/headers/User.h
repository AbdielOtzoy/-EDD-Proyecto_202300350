#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

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

    void printUser();
};

#endif