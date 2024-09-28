#ifndef APPSTAGE_H
#define APPSTAGE_H
#include "structures/avl.h"
#include "structures/doublylist.h"
#include <QObject>
#include "user.h"
#include "models/post.h"
#include "structures/bst.h"

class AppState : public QObject {
    Q_OBJECT

private:
    static AppState* instance;  // Singleton
    Avl* avlTree;  // Árbol AVL como parte del estado global
    User* userLogged; // Usuario Logeado actualmente
    DoublyList* posts; // todas las publicaciones de la aplicación
    BST *feed; // publicaciones disponibles para el usuario

    // Constructor privado para evitar instancias directas
    AppState();

public:
    // Método estático para obtener la única instancia
    static AppState* getInstance();

    // Métodos para interactuar con el árbol AVL
    Avl* getAvlTree();
    void setAvlTree(Avl* tree);

    User* getUserLogged();
    void setUserLogged(User* usuario);

    void agregarPost(Post* post);
    DoublyList* getPosts();
    void setPosts(DoublyList* newPosts);

    BST* getBST();
    void agregarBST(Post* post);
    void setBST(BST* bst);

signals:
    void avlTreeChanged(Avl* newTree);  // Señal si el árbol AVL cambia
    void userLoggedChanged(User* newUser);
};

#endif // APPSTAGE_H
