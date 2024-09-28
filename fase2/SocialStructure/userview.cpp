#include "userview.h"
#include "ui_userview.h"
#include "mainwindow.h"
#include "postform.h"
#include "user.h"
#include "structures/avl.h"
#include <QMessageBox>
#include <QDebug>
#include <QTableWidget>
#include "appstage.h"
#include <QString>
#include <string>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QLabel>
#include <QWidget>

userView::userView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::userView)
{
    ui->setupUi(this);
}

userView::~userView()
{
    delete ui;
}

// cerrar sesion
void userView::on_pushButton_clicked()
{
    // eliminar el userLogged
    AppState *appState = AppState::getInstance();
    User *userlogged = appState->getUserLogged();

    userlogged->setName("");
    userlogged->setLastName("");
    userlogged->setEmail("");
    userlogged->setBirthDate("");
    userlogged->setPassword("");

    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
    this->close();
}


void userView::on_pushButton_3_clicked()
{
    PostForm *postform = new PostForm();
    postform->show();
    this->hide();

}


void userView::on_tabWidget_tabBarClicked(int index)
{
}


void userView::on_tabWidget_currentChanged(int index)
{
    AppState *appState = AppState::getInstance();
    qDebug() << index;
    if(index == 4){
        qDebug() << "cargando datos del perfil ... ";
        User *userlogged = appState->getUserLogged();


        ui->name->setText("Nombres: " + QString::fromStdString(userlogged->getName()));
        ui->lastname->setText("Apellidos: " + QString::fromStdString(userlogged->getLastName()));
        ui->email->setText("Correo: " + QString::fromStdString(userlogged->getEmail()));
        ui->password->setText("Contraseña: " + QString::fromStdString(userlogged->getPassword()));
        ui->birthdate->setText("Fecha de nacimiento: " + QString::fromStdString(userlogged->getBirthDate()));


    }
    if(index == 3) {
        qDebug() << "solicitudes";

        // para la tabla de usuarios
        Avl *avlTree = appState->getAvlTree();
        QTableWidget *users = ui->users;

        //limpiar la tabla
        users->clear();
        users->setRowCount(0);
        users->setHorizontalHeaderLabels(QStringList() << "Nombres" << "Apellidos" << "Correo" << "Nacimiento" << "Enviar Solicitud");



        User *userlogged = appState->getUserLogged();

        // agregar usuarios a la tabla de usuarios
        avlTree->agregarUsuariosATabla(users,userlogged);

        // tabla de solicitudes enviadas
        QTableWidget *solitudesEnviadas = ui->solicitudesEnviadas;

        solitudesEnviadas->clear();
        solitudesEnviadas->setRowCount(0);
        solitudesEnviadas->setHorizontalHeaderLabels(QStringList() << "Correo" << "Cancelar");

        userlogged->requestsSent.agregarSolicitudTabla(solitudesEnviadas, userlogged);

        // tabla de solicitudes recibidas
        QTableWidget *solicitudesRecibidas = ui->solicitudesRecibidas;

        solicitudesRecibidas->clear();
        solicitudesRecibidas->setRowCount(0);
        solicitudesRecibidas->setHorizontalHeaderLabels(QStringList() << "Correo" << "Aceptar" << "Rechazar");

        // llenar la tabla de las solicitudes recibidas
        userlogged->requestsReceived.agregarSolicitudTabla(solicitudesRecibidas, userlogged);


        // ver pos los amigos del usuario
        qDebug() << "los amigso del usuario logeado: ";
        userlogged->friends.printFriendList();

    }
    if(index == 1) { // publicaciones

        //lenar las publicaciones del usuario
        User *userlogged = appState->getUserLogged();
        DoublyList *posts = appState->getPosts(); // publicaciones en general
        BST *bst = new BST();


        posts->printList();

        FriendList friends = userlogged->friends;

        // filtrando las publicaciones
        posts->fillBstPosts(friends, userlogged->getEmail(), *bst);

        qDebug() << "publicaciones disponibles";
        bst->preorder();

        // mostrando las publicaciones en el scroll area
        QScrollArea *feed = ui->feed;


        bst->fillScrollAreaWithPosts(feed);

    }

}



void userView::on_pushButton_2_clicked()
{
    QString email = ui->emailToSearch->toPlainText();

    if(email == "") {
        QMessageBox::warning(this, "error","Debe llenar el campo para buscar al usuario");
    } else {
        AppState *appState = AppState::getInstance();
        Avl *avlTree = appState->getAvlTree();

        User *usertest1 = new User("maria", "lopez", "12/05/1998", "maria.lopez@gmail.com", "password123");
        avlTree->agregar(*usertest1);

        Nodo userFound = avlTree->buscar(email.toStdString());
        if(userFound != NULL) {
            ui->nameFound->setText("Nombres: " + QString::fromStdString(userFound->data.getName()));
            ui->lastnameFound->setText("Apellidos: " + QString::fromStdString(userFound->data.getLastName()));
            ui->emaiFound->setText("Correo: " + QString::fromStdString(userFound->data.getEmail()));
            ui->birthdateFound->setText("Fecha de nacimiento: " + QString::fromStdString(userFound->data.getBirthDate()));
        } else {
            QMessageBox::warning(this, "error","No se ha encontrado el usuario");
        }

    }
}

