#include <iostream>
#include <string>
#include <fstream>
#include "doublylist.h"
#include "friendlist.h"
#include <QDebug>
#include "bst.h"
#include "../models/post.h"

using namespace std;

NodeDoubly::NodeDoubly()
{
    this->post = Post();
    this->next = NULL;
    this->prev = NULL;
}

NodeDoubly::NodeDoubly(Post post)
{
    this->post = post;
    this->next = NULL;
    this->prev = NULL;
}

void NodeDoubly::printNodeDoubly()
{
    this->post.printPost();
}


DoublyList::DoublyList()
{
    this->head = NULL;
    this->tail = NULL;
}

void DoublyList::addNode(Post post)
{
    NodeDoubly *newNode = new NodeDoubly(post);
    if (this->head == NULL)
    {
        this->head = newNode;
        this->tail = newNode;
    }
    else
    {
        this->tail->next = newNode;
        newNode->prev = this->tail;
        this->tail = newNode;
    }
}

void DoublyList::printList()
{
    NodeDoubly *current = this->head;
    while (current != NULL)
    {
        current->printNodeDoubly();
        current = current->next;
    }
}

void DoublyList::deleteNode(string author)
{
    NodeDoubly *current = this->head;
    while (current != NULL)
    {
        if (current->post.getAuthor() == author)
        {
            if (current == this->head)
            {
                this->head = current->next;
                this->head->prev = NULL;
            }
            else if (current == this->tail)
            {
                this->tail = current->prev;
                this->tail->next = NULL;
            }
            else
            {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            delete current;
            return;
        }
        current = current->next;
    }
}

void DoublyList::searchNode(string author)
{
    NodeDoubly *current = this->head;
    while (current != NULL)
    {
        if (current->post.getAuthor() == author)
        {
            current->printNodeDoubly();
            return;
        }
        current = current->next;
    }
    cout << "No se encontro el post" << endl;
}


void DoublyList::createDotFile()
{
    ofstream file;
    file.open("posts.dot");
    if (file.is_open())
    {
        file << "digraph G {" << endl;
        file << "  rankdir=LR;" << endl;                                         // Dirección de izquierda a derecha
        file << "  node [shape=record, style=filled, color=lightblue];" << endl; // Estilo de los nodos

        NodeDoubly *current = this->head;
        int nodeId = 0;

        // Crear nodos con identificadores únicos
        while (current != NULL)
        {
            file << "  node" << nodeId << " [label=\"{"
                 << "Autor: " << current->post.getAuthor() << "|"
                 << "Fecha: " << current->post.getDate() << "|"
                 << "Hora: " << current->post.getTime() << "|"
                 << current->post.getContent() << "}\"];" << endl;
            current = current->next;
            nodeId++;
        }

        // Crear conexiones bidireccionales para representar la lista doblemente enlazada
        current = this->head;
        nodeId = 0;
        while (current != NULL && current->next != NULL)
        {
            file << "  node" << nodeId << " -> node" << (nodeId + 1) << " [dir=both];" << endl; // Conexión en ambas direcciones
            current = current->next;
            nodeId++;
        }

        file << "}" << endl;
        file.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo" << endl;
    }
}

void DoublyList::topFiveUsersWithMostPosts()
{
    // Crear un arreglo de 5 elementos para almacenar los 5 autores con mas publicaciones
    string authors[5];
    int posts[5];
    for (int i = 0; i < 5; i++)
    {
        authors[i] = "";
        posts[i] = 0;
    }
    // Recorrer la lista de publicaciones y contar cuantas publicaciones tiene cada autor
    NodeDoubly *current = this->head;
    while (current != NULL)
    {
        for (int i = 0; i < 5; i++)
        {
            if (current->post.getAuthor() == authors[i])
            {
                posts[i]++;
                break;
            }
            else if (authors[i] == "")
            {
                authors[i] = current->post.getAuthor();
                posts[i]++;
                break;
            }
        }
        current = current->next;
    }
    // Ordenar el arreglo de autores y publicaciones de mayor a menor
    for (int i = 0; i < 5; i++)
    {
        for (int j = i + 1; j < 5; j++)
        {
            if (posts[i] < posts[j])
            {
                int temp = posts[i];
                posts[i] = posts[j];
                posts[j] = temp;
                string tempAuthor = authors[i];
                authors[i] = authors[j];
                authors[j] = tempAuthor;
            }
        }
    }
    // Imprimir los 5 autores con mas publicaciones
    for (int i = 0; i < 5; i++)
    {
        cout << "Autor: " << authors[i] << " Publicaciones: " << posts[i] << endl;
    }
}

void DoublyList::fillBstPosts(FriendList &friends, string loggedUser, BST &bst) {
    NodeDoubly* current = this->head;

    while (current != nullptr) {
        string author = current->post.getAuthor();

        // Verificar si el autor es el usuario logueado o un amigo
        if (author == loggedUser || isFriend(friends, author)) {
            // Insertar la publicación en el árbol BST
            bst.insert(current->post);
        }

        // Moverse al siguiente nodo
        current = current->next;
    }
}

bool DoublyList::isFriend(FriendList &friends, string author) {
    // Recorrer la lista de amigos y comparar los nombres
    for (int i = 0; i < friends.getSize(); ++i) {
        if (friends.get(i) == author) {
            return true;
        }
    }
    return false;
}

void DoublyList::insertCommentByContent(string contentToFind, Comment commentToInsert) {
    NodeDoubly* current = this->head;
    while (current != nullptr) {
        if (current->post.getContent() == contentToFind) {
            // Si se encuentra el post, se inserta el comentario
            current->post.comments.insert(commentToInsert);
            qDebug() << "Comentario agregado a la publicación con contenido:"
                     << QString::fromStdString(contentToFind);
            return;
        }
        current = current->next;
    }
    qDebug() << "No se encontró la publicación con ese contenido.";
}
