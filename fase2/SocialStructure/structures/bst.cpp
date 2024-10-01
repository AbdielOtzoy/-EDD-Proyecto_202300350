#include "bst.h"
#include <QFrame>
#include <QPushButton>
#include <QDebug>
#include "../commentform.h"
#include <QPixmap>
#include <QDir>
#include <QDesktopServices>
#include <QUrl>
#include <set>
// Constructor para el nodo que ahora acepta un Post
Node::Node(Post value){
    this->value = value;
    right = nullptr;
    left = nullptr;
}

Post& Node::getValue() {
    return value;
}


Node* Node::getRight(){
    return right;
}

Node* Node::getLeft(){
    return left;
}

void Node::setValue(Post value){
    this->value = value;
}

void Node::setRight(Node *right){
    this->right = right;
}

void Node::setLeft(Node *left){
    this->left = left;
}

BST::BST(){
    this->root = nullptr;
}

void BST::insert(Post value) {
    this->root = insert(this->root, value);
}

Node* BST::insert(Node* root, Post value) {
    if (root == nullptr) {
        root = new Node(value);
    } else if (compareDates(value.getDate(), value.getTime(), root->getValue().getDate(), root->getValue().getTime())) {
        root->setLeft(insert(root->getLeft(), value));
    } else {
        root->setRight(insert(root->getRight(), value));
    }
    return root;
}

// Comparar dos fechas y horas en formato "dd/mm/yyyy" y "hh:mm:ss"
bool BST::compareDates(string date1, string hour1, string date2, string hour2) {
    tm tm1 = {}, tm2 = {};

    // Procesar las fechas
    istringstream ss1(date1 + " " + hour1);
    istringstream ss2(date2 + " " + hour2);

    // Leer las fechas y horas en el formato correcto
    ss1 >> get_time(&tm1, "%d/%m/%Y %H:%M:%S");
    ss2 >> get_time(&tm2, "%d/%m/%Y %H:%M:%S");

    // Convertir a time_t para comparar
    time_t time1 = mktime(&tm1);
    time_t time2 = mktime(&tm2);

    // Comparar los tiempos
    return difftime(time1, time2) < 0;
}

// Recorrido en preorden para mostrar las publicaciones
void BST::preorder(){
    preorder(root);
}

void BST::preorder(Node *root){
    if (root != nullptr){
        root->getValue().printPost(); // Imprimir los datos de la publicación
        preorder(root->getLeft());
        preorder(root->getRight());
    }
}

void BST::deleteTree(){
    deleteTree(root);
}

void BST::deleteTree(Node* root){
    if (root != nullptr){
        deleteTree(root->getLeft());
        deleteTree(root->getRight());
        delete root;
    }
}


void BST::graph(const std::string &highlightedDate) {
    ofstream outfile("bst.dot");
    outfile << "digraph G {" << endl;

    if (root != nullptr) {
        // Utilizamos un conjunto para evitar repetir fechas
        std::set<std::string> uniqueDates;
        graph(root, outfile, uniqueDates, highlightedDate);
    }

    outfile << "}" << endl;
    outfile.close();
    system("dot -Tpng ./bst.dot -o ./bst.png");
}

void BST::graph(Node *root, ofstream &content, std::set<std::string> &uniqueDates, const std::string &highlightedDate) {
    if (root != nullptr) {
        std::string currentDate = root->getValue().getDate();

        // Solo graficamos la fecha si no ha sido ya graficada
        if (uniqueDates.find(currentDate) == uniqueDates.end()) {
            uniqueDates.insert(currentDate);

            // Revisar si la fecha es la que queremos destacar
            if (currentDate == highlightedDate) {
                // Nodo con fondo verde si es la fecha destacada
                content << "Nodo" << root << "[label = \"" << currentDate << "\", style=filled, fillcolor=green]" << endl;
            } else {
                // Nodo normal
                content << "Nodo" << root << "[label = \"" << currentDate << "\"]" << endl;
            }
        }

        // Graficar las conexiones, pero solo si los nodos hijos tienen fechas diferentes
        if (root->getLeft() != nullptr && uniqueDates.find(root->getLeft()->getValue().getDate()) == uniqueDates.end()) {
            content << "Nodo" << root << " -> Nodo" << root->getLeft() << endl;
        }

        if (root->getRight() != nullptr && uniqueDates.find(root->getRight()->getValue().getDate()) == uniqueDates.end()) {
            content << "Nodo" << root << " -> Nodo" << root->getRight() << endl;
        }

        // Llamada recursiva a los nodos izquierdo y derecho
        this->graph(root->getLeft(), content, uniqueDates, highlightedDate);
        this->graph(root->getRight(), content, uniqueDates, highlightedDate);
    }
}

void BST::insertComment(Post postToFind, Comment commentToInsert) {
    Node* foundNode = search(root, postToFind);
    if (foundNode != nullptr) {
        // Insertar el comentario en la publicación encontrada
        foundNode->getValue().comments.insert(commentToInsert);
        qDebug() << "Comentario agregado a la publicación con fecha:"
                 << QString::fromStdString(postToFind.getDate())
                 << " y hora: " << QString::fromStdString(postToFind.getTime());
    } else {
        qDebug() << "Publicación no encontrada.";
    }
}

Node* BST::search(Node* root, Post postToFind) {
    if (root == nullptr) {
        return nullptr;
    }

    // Compara las fechas y horas
    if (compareDates(postToFind.getDate(), postToFind.getTime(), root->getValue().getDate(), root->getValue().getTime())) {
        return search(root->getLeft(), postToFind);
    } else if (compareDates(root->getValue().getDate(), root->getValue().getTime(), postToFind.getDate(), postToFind.getTime())) {
        return search(root->getRight(), postToFind);
    } else {
        // Si las fechas y horas coinciden, se ha encontrado la publicación
        return root;
    }
}

// Método para llenar el QScrollArea con los posts del BST
void BST::fillScrollAreaWithPosts(QScrollArea *scrollArea) {
    // Crear un widget contenedor para los elementos
    QWidget *container = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(container); // Layout vertical para los posts

    // Llenar el layout con las publicaciones
    fillScrollAreaWithPosts(this->root, layout);

    // Configurar el widget contenedor en el scroll area
    container->setLayout(layout);
    scrollArea->setWidget(container);
    scrollArea->setWidgetResizable(true); // Permitir que el contenido se ajuste al tamaño del área de desplazamiento
}

// Método recursivo que agrega cada post al layout
void BST::fillScrollAreaWithPosts(Node *node, QVBoxLayout *layout) {
    if (node != nullptr) {
        // Crear un widget para mostrar los datos del post
        QWidget *postWidget = new QWidget();
        QVBoxLayout *postLayout = new QVBoxLayout(postWidget);

        // Crear etiquetas con la información del post
        QLabel *authorLabel = new QLabel(QString::fromStdString("Autor: " + node->getValue().getAuthor()));
        QLabel *dateLabel = new QLabel(QString::fromStdString("Fecha: " + node->getValue().getDate() + " Hora: " + node->getValue().getTime()));
        QLabel *contentLabel = new QLabel(QString::fromStdString("Contenido: " + node->getValue().getContent()));

        // Aplicar estilos a las etiquetas
        authorLabel->setStyleSheet("font-size: 18px; font-weight: bold; text-align: center; color: #333;");
        dateLabel->setStyleSheet("font-size: 16px; text-align: center; color: #555;");
        contentLabel->setStyleSheet("font-size: 14px; text-align: center; color: #777;");

        // Añadir las etiquetas al layout del post
        postLayout->addWidget(authorLabel);
        postLayout->addWidget(dateLabel);
        postLayout->addWidget(contentLabel);

        // Crear el botón de comentar
        QPushButton *commentButton = new QPushButton("Comentar");
        commentButton->setStyleSheet("font-size: 14px; padding: 5px; background-color: #007BFF; color: white; border: none; border-radius: 5px;");

        // Conectar el botón con la acción de imprimir el contenido del post en la consola
        QObject::connect(commentButton, &QPushButton::clicked, [node]() {
            // Obtener un puntero al Post en lugar de una copia
            Post* post = &node->getValue(); // Esto ya no causará problemas


            // Pasar el puntero a CommentForm
            CommentForm *commentForm = new CommentForm(post);
            commentForm->show();

        });

        // Crear el botón de ver comentarios
        QPushButton *verComentarios = new QPushButton("Ver Comentarios");
        verComentarios->setStyleSheet("font-size: 14px; padding: 5px; background-color: #007BFF; color: white; border: none; border-radius: 5px;");

        // Conectar el botón con la acción de imprimir el contenido del post en la consola
        QObject::connect(verComentarios, &QPushButton::clicked, [node]() {

            qDebug() << "ver comentarios de la publicación: " << node->getValue().getContent();
            node->getValue().comments.graph();

            QString imagePath = QDir::currentPath() + "/btree_comments.png";
            qDebug() << imagePath;
            // Cargar la imagen en un QPixmap
            QPixmap image(imagePath);
            // Verificar si la imagen se cargó correctamente
            if (!image.isNull())
            {
                // Abrir la imagen con la aplicación predeterminada del sistema operativo
                QDesktopServices::openUrl(QUrl::fromLocalFile(imagePath));
            }

        });

        // Añadir el botón al layout del post
        postLayout->addWidget(verComentarios);

        // Añadir el botón al layout del post
        postLayout->addWidget(commentButton);

        // Crear un layout para los comentarios
        QVBoxLayout *commentLayout = new QVBoxLayout();
        QLabel *commentsLabel = new QLabel("Comentarios:");
        commentLayout->addWidget(commentsLabel);

        // Llenar el layout con los comentarios del árbol B relacionado con el post
        node->getValue().comments.fillLayoutWithComments(commentLayout);
        postLayout->addLayout(commentLayout);

        // Aplicar estilos al widget de la publicación (fondo blanco y bordes redondeados)
        postWidget->setStyleSheet("background-color: white; border-radius: 10px; padding: 10px;");

        // Ajustar el tamaño y la alineación del contenido del post
        postLayout->setAlignment(Qt::AlignCenter);

        // Añadir el widget del post al layout principal
        layout->addWidget(postWidget);

        // Añadir espacio entre cada publicación
        layout->addSpacing(10);

        // Recursión para los nodos izquierdo y derecho
        fillScrollAreaWithPosts(node->getLeft(), layout);
        fillScrollAreaWithPosts(node->getRight(), layout);
    }
}

// Método para llenar el QScrollArea con los posts del BST
void BST::fillScrollAreaOrden(QScrollArea *scrollArea, string orden, int cantidad) {
    // Crear un widget contenedor para los elementos
    QWidget *container = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(container); // Layout vertical para los posts

    // Llenar el layout con las publicaciones
    fillScrollAreaOrden(this->root, layout, orden, cantidad);

    // Configurar el widget contenedor en el scroll area
    container->setLayout(layout);
    scrollArea->setWidget(container);
    scrollArea->setWidgetResizable(true); // Permitir que el contenido se ajuste al tamaño del área de desplazamiento
}

void BST::fillScrollAreaOrden(Node *node, QVBoxLayout *layout, string orden, int &cantidad) {
    if (node != nullptr && cantidad > 0) {

        // Preorden: procesar el nodo antes de los subárboles
        if(orden == "PreOrden") {
            procesarNodo(node, layout, cantidad);
            fillScrollAreaOrden(node->getLeft(), layout, orden, cantidad);
            fillScrollAreaOrden(node->getRight(), layout, orden, cantidad);
        }

        // Inorden: procesar el nodo entre los subárboles
        else if(orden == "InOrden") {
            fillScrollAreaOrden(node->getLeft(), layout, orden, cantidad);
            procesarNodo(node, layout, cantidad);
            fillScrollAreaOrden(node->getRight(), layout, orden, cantidad);
        }

        // Postorden: procesar el nodo después de los subárboles
        else if(orden == "PostOrden") {
            fillScrollAreaOrden(node->getLeft(), layout, orden, cantidad);
            fillScrollAreaOrden(node->getRight(), layout, orden, cantidad);
            procesarNodo(node, layout, cantidad);
        }
    }
}

// Función auxiliar para procesar un nodo (crear el widget del post y reducir la cantidad)
void BST::procesarNodo(Node *node, QVBoxLayout *layout, int &cantidad) {
    if (cantidad <= 0) return; // Verifica si ya se alcanzó el límite

    // Crear el widget de la publicación y añadirlo al layout (igual que en tu código original)
    QWidget *postWidget = new QWidget();
    QVBoxLayout *postLayout = new QVBoxLayout(postWidget);
    QLabel *authorLabel = new QLabel(QString::fromStdString("Autor: " + node->getValue().getAuthor()));
    QLabel *dateLabel = new QLabel(QString::fromStdString("Fecha: " + node->getValue().getDate() + " Hora: " + node->getValue().getTime()));
    QLabel *contentLabel = new QLabel(QString::fromStdString("Contenido: " + node->getValue().getContent()));

    // Aplicar estilos a las etiquetas
    authorLabel->setStyleSheet("font-size: 18px; font-weight: bold; text-align: center; color: #333;");
    dateLabel->setStyleSheet("font-size: 16px; text-align: center; color: #555;");
    contentLabel->setStyleSheet("font-size: 14px; text-align: center; color: #777;");

    postLayout->addWidget(authorLabel);
    postLayout->addWidget(dateLabel);
    postLayout->addWidget(contentLabel);

    // Crear el botón de comentar
    QPushButton *commentButton = new QPushButton("Comentar");
    commentButton->setStyleSheet("font-size: 14px; padding: 5px; background-color: #007BFF; color: white; border: none; border-radius: 5px;");

    // Conectar el botón con la acción de imprimir el contenido del post en la consola
    QObject::connect(commentButton, &QPushButton::clicked, [node]() {
        // Obtener un puntero al Post en lugar de una copia
        Post* post = &node->getValue(); // Esto ya no causará problemas


        // Pasar el puntero a CommentForm
        CommentForm *commentForm = new CommentForm(post);
        commentForm->show();

    });

    // Añadir el botón al layout del post
    postLayout->addWidget(commentButton);

    // Crear un layout para los comentarios
    QVBoxLayout *commentLayout = new QVBoxLayout();
    QLabel *commentsLabel = new QLabel("Comentarios:");
    commentLayout->addWidget(commentsLabel);

    // Llenar el layout con los comentarios del árbol B relacionado con el post
    node->getValue().comments.fillLayoutWithComments(commentLayout);
    postLayout->addLayout(commentLayout);

    // Aplicar estilos al widget de la publicación (fondo blanco y bordes redondeados)
    postWidget->setStyleSheet("background-color: white; border-radius: 10px; padding: 10px;");

    // Ajustar el tamaño y la alineación del contenido del post
    postLayout->setAlignment(Qt::AlignCenter);


    layout->addWidget(postWidget);
    layout->addSpacing(10);

    cantidad--; // Decrementar la cantidad solo cuando se procesa el nodo
}



// Método para llenar el QScrollArea con los posts del BST por fecha de búsqueda
void BST::fillScrollAreaWithPosts(QScrollArea *scrollArea, string dateFilter) {
    // Crear un widget contenedor para los elementos
    QWidget *container = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(container); // Layout vertical para los posts

    // Llenar el layout con las publicaciones
    fillScrollAreaWithPosts(this->root, layout, dateFilter);

    // Configurar el widget contenedor en el scroll area
    container->setLayout(layout);
    scrollArea->setWidget(container);
    scrollArea->setWidgetResizable(true); // Permitir que el contenido se ajuste al tamaño del área de desplazamiento
}

// Método recursivo que agrega cada post al layout por filtro
void BST::fillScrollAreaWithPosts(Node *node, QVBoxLayout *layout, string dateFilter) {
    if (node != nullptr & node->getValue().getDate() == dateFilter) {
        // Crear un widget para mostrar los datos del post
        QWidget *postWidget = new QWidget();
        QVBoxLayout *postLayout = new QVBoxLayout(postWidget);

        // Crear etiquetas con la información del post
        QLabel *authorLabel = new QLabel(QString::fromStdString("Autor: " + node->getValue().getAuthor()));
        QLabel *dateLabel = new QLabel(QString::fromStdString("Fecha: " + node->getValue().getDate() + " Hora: " + node->getValue().getTime()));
        QLabel *contentLabel = new QLabel(QString::fromStdString("Contenido: " + node->getValue().getContent()));

        // Aplicar estilos a las etiquetas
        authorLabel->setStyleSheet("font-size: 18px; font-weight: bold; text-align: center; color: #333;");
        dateLabel->setStyleSheet("font-size: 16px; text-align: center; color: #555;");
        contentLabel->setStyleSheet("font-size: 14px; text-align: center; color: #777;");

        // Añadir las etiquetas al layout del post
        postLayout->addWidget(authorLabel);
        postLayout->addWidget(dateLabel);
        postLayout->addWidget(contentLabel);

        // Crear el botón de comentar
        QPushButton *commentButton = new QPushButton("Comentar");
        commentButton->setStyleSheet("font-size: 14px; padding: 5px; background-color: #007BFF; color: white; border: none; border-radius: 5px;");

        // Conectar el botón con la acción de imprimir el contenido del post en la consola
        QObject::connect(commentButton, &QPushButton::clicked, [node]() {
            // Obtener un puntero al Post en lugar de una copia
            Post* post = &node->getValue(); // Esto ya no causará problemas


            // Pasar el puntero a CommentForm
            CommentForm *commentForm = new CommentForm(post);
            commentForm->show();

        });


        postLayout->addWidget(commentButton);

        // Crear un layout para los comentarios
        QVBoxLayout *commentLayout = new QVBoxLayout();
        QLabel *commentsLabel = new QLabel("Comentarios:");
        commentLayout->addWidget(commentsLabel);

        // Llenar el layout con los comentarios del árbol B relacionado con el post
        node->getValue().comments.fillLayoutWithComments(commentLayout);
        postLayout->addLayout(commentLayout);

        // Aplicar estilos al widget de la publicación (fondo blanco y bordes redondeados)
        postWidget->setStyleSheet("background-color: white; border-radius: 10px; padding: 10px;");

        // Ajustar el tamaño y la alineación del contenido del post
        postLayout->setAlignment(Qt::AlignCenter);

        // Añadir el widget del post al layout principal
        layout->addWidget(postWidget);

        // Añadir espacio entre cada publicación
        layout->addSpacing(10);

        // Recursión para los nodos izquierdo y derecho
        fillScrollAreaWithPosts(node->getLeft(), layout);
        fillScrollAreaWithPosts(node->getRight(), layout);

        // ver si hay comentarios
        qDebug() << "comentarios: ";
        node->getValue().comments.printTree();
    }
}

BST::~BST(){
    deleteTree(this->root);
}

