#ifndef USER_H
#define USER_H
#include <string>
#include "structures/list.h" // lista para solicitudes enviadas
#include "structures/friendlist.h" // lista para amigos
#include "structures/stack.h" // Pila para almacenar las solicitudes recibidas
#include "models/request.h"
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
    List requestsSent;
    Stack requestsReceived;
    FriendList friends;

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

    void addRequestSent(Request request);
    void addRequestReceived(Request request);
    void printRequestsSent();
    void printRequestsReceived();
    void removeRequestSent(Request request);
    void removeRequestReceived();

    void addFriend(string name);
    int getSizeFriends();
    void printFriends();

};

#endif // USER_H
