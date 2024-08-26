#ifndef AUTH_H
#define AUTH_H
#include <iostream>
#include "../../models/headers/User.h"

extern bool isLogged;
extern bool isAdmin;
extern User loggedUser;

void addTestData();
void loginUser();
void registerUser();
void logoutUser();
void logoutAdmin();
void sendRequest();
void respondRequest();
void createPost();
void viewProfile();
void viewMyFriends();
void viewAvailablePosts();
void deleteAccount();
void loadUsers();
void loadRequests();
void loadPosts();

// reportes para admin
void viewUsers();
void viewMatrix();
void viewPosts();
void viewTopFiveUsersWithMostPosts();
void viewTopFiveUsersWithLeastFriends();

// reportes para usuario
void viewSentRequests();
void viewReceivedRequests();
void viewAvailablePostsDotFile();

#endif