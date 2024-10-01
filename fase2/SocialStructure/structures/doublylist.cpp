#include <iostream>
#include <string>
#include <fstream>
#include "doublylist.h"
#include "friendlist.h"
#include <QDebug>
#include <map>
#include <vector>
#include <algorithm>
#include <QString>
#include <QTableWidget>
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
                 << "Autor: " << current->post.getAuthor() << "\\l"
                 << "Fecha: " << current->post.getDate() << "\\l"
                 << "Hora: " << current->post.getTime() << "\\l"
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

        stringstream ss;
        file << ss.str();
        file << "}" << endl;
        file.close();
        system("dot -Tpng posts.dot -o posts.png");
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

// Método para llenar un QTableWidget con las tres fechas con más publicaciones
void DoublyList::fillTableWithTopDates(QTableWidget* tableWidget) {
    // Crear un mapa para contar la cantidad de publicaciones por fecha
    std::map<std::string, int> dateCount;
    NodeDoubly* current = this->head;

    // Recorrer la lista y contar las publicaciones por fecha
    while (current != nullptr) {
        std::string date = current->post.getDate();
        dateCount[date]++;
        current = current->next;
    }

    // Convertir el mapa en un vector de pares (fecha, cantidad de publicaciones)
    std::vector<std::pair<std::string, int>> dateVector(dateCount.begin(), dateCount.end());

    // Ordenar el vector en función de la cantidad de publicaciones de forma descendente
    std::sort(dateVector.begin(), dateVector.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        return a.second > b.second;
    });

    // Limpiar la tabla antes de llenarla
    tableWidget->clear();

    // Configurar el número de filas y columnas de la tabla
    tableWidget->setRowCount(3);
    tableWidget->setColumnCount(2);

    // Configurar las cabeceras de la tabla
    QStringList headers;
    headers << "Fecha" << "Cantidad de Publicaciones";
    tableWidget->setHorizontalHeaderLabels(headers);

    // Llenar la tabla con las tres primeras fechas
    for (int i = 0; i < 3 && i < dateVector.size(); ++i) {
        QString date = QString::fromStdString(dateVector[i].first);
        QString count = QString::number(dateVector[i].second);

        // Insertar la fecha y la cantidad de publicaciones en las celdas correspondientes
        tableWidget->setItem(i, 0, new QTableWidgetItem(date));
        tableWidget->setItem(i, 1, new QTableWidgetItem(count));
    }
}

void DoublyList::fillTableWithTopPostsComments(QTableWidget *tableWidget) {
    // Crear un vector para almacenar las publicaciones junto con su conteo de comentarios
    std::vector<std::pair<Post, int>> postsWithComments;
    NodeDoubly* current = this->head;

    // Recorrer la lista y contar los comentarios para cada publicación
    while (current != nullptr) {
        int commentCount = current->post.comments.countNodes(); // Obtener la cantidad de comentarios
        postsWithComments.emplace_back(current->post, commentCount); // Almacenar publicación y su conteo
        current = current->next;
    }

    // Ordenar el vector en función de la cantidad de comentarios de forma descendente
    std::sort(postsWithComments.begin(), postsWithComments.end(), [](const auto& a, const auto& b) {
        return a.second > b.second; // Ordenar por el conteo de comentarios
    });

    // Limpiar la tabla antes de llenarla
    tableWidget->clear();

    // Configurar el número de filas y columnas de la tabla
    tableWidget->setRowCount(3);
    tableWidget->setColumnCount(3); // Tres columnas: Autor, Cantidad de Comentarios, Contenido

    // Configurar las cabeceras de la tabla
    QStringList headers;
    headers << "fecha" << "Usuario" << "No. comentarios";
    tableWidget->setHorizontalHeaderLabels(headers);

    // Llenar la tabla con las tres publicaciones con más comentarios
    for (int i = 0; i < 3 && i < postsWithComments.size(); ++i) {
        const Post& post = postsWithComments[i].first;
        QString date = QString::fromStdString(post.getDate());
        QString author = QString::fromStdString(post.getAuthor());
        QString count = QString::number(postsWithComments[i].second);

        // Insertar en las celdas correspondientes
        tableWidget->setItem(i, 0, new QTableWidgetItem(date));
        tableWidget->setItem(i, 1, new QTableWidgetItem(author));
        tableWidget->setItem(i, 2, new QTableWidgetItem(count));
    }
}

