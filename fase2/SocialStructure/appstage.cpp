#include "appstage.h"
#include "structures/doublylist.h"
#include "models/post.h"
#include "structures/bst.h"

// Inicializar la instancia estática a nullptr
AppState* AppState::instance = nullptr;

// Constructor privado
AppState::AppState() {
    avlTree = new Avl();  // Crear el árbol AVL cuando se inicialice el estado global
    userLogged = new User();
    posts = new DoublyList();
    feed = new BST();
}

// Obtener la instancia de AppState
AppState* AppState::getInstance() {
    if (instance == nullptr) {
        instance = new AppState();
    }
    return instance;
}

// Obtener el árbol AVL
Avl* AppState::getAvlTree() {
    return avlTree;
}

// Configurar un nuevo árbol AVL
void AppState::setAvlTree(Avl* tree) {
    avlTree = tree;
    emit avlTreeChanged(avlTree);  // Emitir señal si el árbol cambia
}

User* AppState::getUserLogged() {
    return userLogged;
}

void AppState::setUserLogged(User* user) {
    userLogged = user;
    emit userLoggedChanged(userLogged);
}

void AppState::agregarPost(Post *post) {
    posts->addNode(*post);
}

DoublyList* AppState::getPosts() {
    return posts;
}

void AppState::setPosts(DoublyList *newPosts) {
    posts = newPosts;
}

BST* AppState::getBST() {
    return feed;
}

void AppState::agregarBST(Post *post) {
    feed->insert(*post);
}

void AppState::setBST(BST *bst) {
    feed = bst;
}
