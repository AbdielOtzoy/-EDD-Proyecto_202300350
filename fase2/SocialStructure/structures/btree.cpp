#include "btree.h"
#include <queue>
#include <QDebug>
#include <QWidget>
#include <QLabel>

Page::Page()
{
    for (int i = 0; i < degree; i++)
    {
        branches[i] = nullptr;
    }

    count = 0;
}

bool Page::fullPage()
{
    return this->count == degree - 1;
}

BTree::BTree()
{
    root = nullptr;
}

void BTree::insert(Comment key)
{
    insert(&root, key);
}

void BTree::insert(Page **root, Comment key)
{
    bool goUp = false;
    Comment median;
    Page *newPage;

    push(*root, key, goUp, median, &newPage);

    if (goUp)
    {
        Page *newRoot = new Page();
        newRoot->count = 1;
        newRoot->keys[1] = median;
        newRoot->branches[0] = *root;
        newRoot->branches[1] = newPage;
        *root = newRoot;
    }
}

void BTree::push(Page *currentPage, Comment key, bool &goUp, Comment &median, Page **newPage)
{
    int k = 0;
    if (currentPage == nullptr)
    {
        goUp = true;
        median = key;
        *newPage = nullptr;
    }
    else
    {
        // Buscar la posición donde debería insertarse el comentario
        bool node_repeated = searchNodeOnPage(currentPage, key, k);
        if (node_repeated)
        {
            cout << "Comentario duplicado en la fecha y hora: " << key.getDate() << " " << key.getTime() << endl;
            goUp = false;
            return;
        }
        push(currentPage->branches[k], key, goUp, median, newPage);
        /* Devuelve control y vuelve por el camino de búsqueda */
        if (goUp)
        {
            if (currentPage->fullPage())
            {
                split(currentPage, median, *newPage, k, median, newPage);
            }
            else
            {
                goUp = false;
                pushNode(currentPage, median, *newPage, k);
            }
        }
    }
}

void BTree::split(Page *current, Comment key, Page *rd, int k, Comment &median, Page **newPage)
{
    int medianPosition = (k <= degree / 2) ? degree / 2 : degree / 2 + 1;
    *newPage = new Page();
    for (int i = medianPosition + 1; i < degree; i++)
    {
        (*newPage)->keys[i - medianPosition] = current->keys[i];
        (*newPage)->branches[i - medianPosition] = current->branches[i];
    }
    (*newPage)->count = (degree - 1) - medianPosition;
    current->count = medianPosition;

    if (k <= degree / 2)
    {
        pushNode(current, key, rd, k);
    }
    else
    {
        pushNode(*newPage, key, rd, k - medianPosition);
    }

    median = current->keys[current->count];
    (*newPage)->branches[0] = current->branches[current->count];
    current->count--;
}

bool BTree::searchNodeOnPage(Page *current, Comment key, int &k)
{
    // Comparar las fechas y horas de los comentarios
    auto compare = [](const Comment &a, const Comment &b)
    {
        if (a.getDate() == b.getDate())
            return a.getTime() < b.getTime();
        return a.getDate() < b.getDate();
    };

    if (compare(key, current->keys[1]))
    {
        k = 0;
        return false;
    }
    else
    {
        k = current->count;
        while (compare(key, current->keys[k]) && k > 1)
        {
            k--;
        }
        return !compare(key, current->keys[k]) && !compare(current->keys[k], key);
    }
}

void BTree::pushNode(Page *current, Comment key, Page *rd, int k)
{
    for (int i = current->count; i >= k + 1; i--)
    {
        current->keys[i + 1] = current->keys[i];
        current->branches[i + 1] = current->branches[i];
    }

    current->keys[k + 1] = key;
    current->branches[k + 1] = rd;
    current->count++;
}

void BTree::getContent(Page *current, stringstream &accum, int &countNode, int &countAux, stringstream &accumLink) {
    if (current == nullptr) {
        return;
    }

    // Create a node in DOT
    accum << "node" << countNode << "[label=\"";
    accum << "<r0>";

    // If there are branches to the left of the first comment
    if (current->branches[0] != nullptr) {
        accumLink << "\"node" << countNode << "\":r0 ->";
        countAux++;
        accumLink << "\"node" << countAux << "\"\n";
    }

    // Iterate over the comments in the current page
    for (int i = 1; i <= current->count; i++) {
        accum << "|";

        // Extract the current comment
        Comment comment = current->keys[i];

        // Show the date and time of the comment as an identifier
        accum << "<c" << i << "> " << comment.getDate() << " " << comment.getTime();
        accum << "|<r" << i << ">";

        // If there are branches to the right of this comment
        if (current->branches[i] != nullptr) {
            accumLink << "\"node" << countNode << "\":r" << i << " -> ";
            countAux++;
            accumLink << "\"node" << countAux << "\"\n";
        }
    }

    accum << "\"];\n";

    // Recursively traverse the tree and generate DOT code for all nodes
    for (int i = 0; i <= current->count; i++) {
        getContent(current->branches[i], accum, countNode, countAux, accumLink);
    }
}

void BTree::write_dot(string code)
{
    ofstream outfile("btree_comments.dot");
    if (outfile.is_open())
    {
        outfile << code;
        outfile.close();

        // Genera la imagen del árbol B en formato PNG
        int returnCode = system("dot -Tpng btree_comments.dot -o btree_comments.png");
        if (returnCode == 0)
        {
            cout << "El archivo PNG fue generado correctamente." << endl;
        }
        else
        {
            cout << "Error al generar el archivo PNG: " << returnCode << endl;
        }
    }
    else
    {
        cerr << "No se pudo abrir el archivo para escribir." << endl;
    }
}
void BTree::graph()
{
    stringstream outfile, accumLinks;
    outfile << "digraph G {\n"
            << "node [shape=record,height=.1];\n";

    if (root != nullptr)
    {
        int countNode = 0;
        int countAux = 0;

        queue<Page *> myqueue;
        myqueue.push(root);

        while (!myqueue.empty())
        {
            Page *current = myqueue.front();
            myqueue.pop();

            // Obtiene el contenido de la página actual
            getContent(current, outfile, countNode, countAux, accumLinks);

            // Agrega las ramas de la página actual a la cola
            for (int i = 0; i <= current->count; i++)
            {
                if (current->branches[i] != nullptr)
                {
                    myqueue.push(current->branches[i]);
                }
            }
            countNode++;
        }

        // Agrega los enlaces entre nodos
        outfile << "\n"
                << accumLinks.str();
    }

    outfile << "}" << endl;

    // Escribe el archivo DOT
    write_dot(outfile.str());
}

bool BTree::isEmpty() {
    if (root != nullptr) {
        return false;
    }
    return true;
}

void BTree::printTree() {
    printTree(root);
}

void BTree::printTree(Page *currentPage) {
    if (currentPage == nullptr) {
        return;
    }

    // Recorre las ramas y los comentarios en in-order
    for (int i = 0; i < currentPage->count; i++) {
        // Imprime los comentarios en las ramas a la izquierda del actual
        printTree(currentPage->branches[i]);

        // Imprime el comentario actual
        Comment comment = currentPage->keys[i + 1]; // Los comentarios inician en 1
        qDebug() << "Author:" << QString::fromStdString(comment.getAuthor());
        qDebug() << "Date:" << QString::fromStdString(comment.getDate());
        qDebug() << "Time:" << QString::fromStdString(comment.getTime());
        qDebug() << "Content:" << QString::fromStdString(comment.getContent());
        qDebug() << "--------------------------";
    }

    // Recorre la rama a la derecha del último comentario
    printTree(currentPage->branches[currentPage->count]);
}

// Método para llenar el QVBoxLayout con los comentarios del árbol B
void BTree::fillLayoutWithComments(QVBoxLayout *layout) {
    fillLayoutWithComments(root, layout);
}

// Método recursivo para agregar los comentarios al layout
void BTree::fillLayoutWithComments(Page *currentPage, QVBoxLayout *layout) {
    if (currentPage == nullptr) {
        return;
    }

    // Recorrer las ramas y los comentarios en in-order
    for (int i = 0; i < currentPage->count; i++) {
        // Añadir los comentarios de las ramas a la izquierda del actual
        fillLayoutWithComments(currentPage->branches[i], layout);

        // Crear un widget para mostrar los datos del comentario
        QWidget *commentWidget = new QWidget();
        QVBoxLayout *commentLayout = new QVBoxLayout(commentWidget);

        // Extraer el comentario actual
        Comment comment = currentPage->keys[i + 1]; // Los comentarios inician en 1

        // Crear etiquetas con la información del comentario
        QLabel *authorLabel = new QLabel(QString::fromStdString("Autor: " + comment.getAuthor()));
        QLabel *dateLabel = new QLabel(QString::fromStdString("Fecha: " + comment.getDate() + " Hora: " + comment.getTime()));
        QLabel *contentLabel = new QLabel(QString::fromStdString("Contenido: " + comment.getContent()));

        // Aplicar estilos a las etiquetas
        authorLabel->setStyleSheet("font-size: 14px; font-weight: bold; color: #333;");
        dateLabel->setStyleSheet("font-size: 12px; color: #555;");
        contentLabel->setStyleSheet("font-size: 12px; color: #777;");

        // Añadir las etiquetas al layout del comentario
        commentLayout->addWidget(authorLabel);
        commentLayout->addWidget(dateLabel);
        commentLayout->addWidget(contentLabel);

        // Aplicar estilos al widget del comentario
        commentWidget->setStyleSheet("background-color: #f9f9f9; border-radius: 5px; padding: 5px;");
        commentLayout->setAlignment(Qt::AlignCenter);

        // Añadir el widget del comentario al layout principal
        layout->addWidget(commentWidget);

        // Añadir espacio entre cada comentario
        layout->addSpacing(5);
    }

    // Recorrer la rama a la derecha del último comentario
    fillLayoutWithComments(currentPage->branches[currentPage->count], layout);
}

int BTree::countNodes() {
    return countNodes(root);
}

int BTree::countNodes(Page *currentPage) {
    if (currentPage == nullptr) {
        return 0; // Si la página es nula, no hay nodos
    }

    int total = currentPage->count; // Contamos los nodos (comentarios) en la página actual

    // Recorremos cada rama (subpágina) y sumamos los nodos de cada una
    for (int i = 0; i <= currentPage->count; i++) {
        total += countNodes(currentPage->branches[i]); // Sumar los nodos de la rama
    }

    return total; // Devolvemos el total de nodos
}

