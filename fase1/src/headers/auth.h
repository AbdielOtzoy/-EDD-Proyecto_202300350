#ifndef AUTH_H
#define AUTH_H
#include <iostream>
#include "../../models/headers/User.h"

extern bool isLogged;
extern bool isAdmin;
extern User loggedUser;

void addTestUsers();
void loginUser();
void registerUser();
void logoutUser();

#endif