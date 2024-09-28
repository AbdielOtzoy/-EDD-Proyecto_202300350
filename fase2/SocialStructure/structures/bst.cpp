#include "bst.h"
#include <QFrame>
#include <QPushButton>
#include <QDebug>
#include "../commentform.h"
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

void BST::graph(){
    ofstream outfile("bst.dot");
    outfile << "digraph G {" << endl;

    if (root != nullptr){
        graph(root, outfile);
    }

    outfile << "}" << endl;
    outfile.close();
    system("dot -Tpng ./bst.dot -o ./bst.png");
}

void BST::graph(Node *root, ofstream &content){
    if (root != nullptr){
        content << "Nodo" << root << "[label = \"" + root->getValue().getDate() + "\"]" << endl;

        if (root->getLeft() != nullptr){
            content << "Nodo" << root << "->Nodo" << root->getLeft() << endl;
        }

        if (root->getRight() != nullptr){
            content << "Nodo" << root << "->Nodo" << root->getRight() << endl;
        }

        this->graph(root->getLeft(), content);
        this->graph(root->getRight(), content);
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

        // ver si hay comentarios
        qDebug() << "comentarios: ";
        node->getValue().comments.printTree();
    }
}


BST::~BST(){
    deleteTree(this->root);
}

