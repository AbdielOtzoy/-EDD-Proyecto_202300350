#include <iostream>
#include <string>
#include <fstream>
#include "./headers/list.h"
#include "../../models/headers/Post.h"
#include "../doublyCircleList/list.h"

using namespace std;

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

// Filtrar posts por autor e insertarlos en una lista circular doblemente enlazada
void DoublyList::filterByAuthor(string author, DoublyCircleList &list)
{
    NodeDoubly *current = this->head;
    while (current != NULL)
    {
        if (current->post.getAuthor() == author)
        {
            list.insert(current->post);
        }
        current = current->next;
    }
}

// implementacion de la funcion createDotFile
void DoublyList::createDotFile()
{
    ofstream file;
    file.open("posts.dot");
    if (file.is_open())
    {
        file << "digraph G {" << endl;
        NodeDoubly *current = this->head;
        // el autor tiene caracteres especiales que deben ser escapados al igual que la fecha y hora
        while (current != NULL)
        {
            file << "\"" << current->post.getAuthor() << " " << current->post.getDate() << " " << current->post.getTime() << "\" [label=\"" << current->post.getContent() << "\"];" << endl;
            current = current->next;
        }
        current = this->head;
        while (current != NULL)
        {
            if (current->next != NULL)
            {
                file << "\"" << current->post.getAuthor() << " " << current->post.getDate() << " " << current->post.getTime() << "\" -> \"" << current->next->post.getAuthor() << " " << current->next->post.getDate() << " " << current->next->post.getTime() << "\";" << endl;
            }
            current = current->next;
        }
        file << "}";
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