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
#include <QPixmap>
#include <QDir>
#include <QDesktopServices>
#include <QUrl>
#include "mainwindow.h"

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

        ui->nameInput->setPlainText(QString::fromStdString(userlogged->getName()));
        ui->lastnameInput->setPlainText(QString::fromStdString(userlogged->getLastName()));
        ui->emailLabel->setText(QString::fromStdString(userlogged->getEmail()));
        ui->passwordInput->setPlainText(QString::fromStdString(userlogged->getPassword()));
        ui->birthdateInput->setPlainText(QString::fromStdString(userlogged->getBirthDate()));



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
    if(index == 2) { // reportes

    QTableWidget *topPostDate = ui->topPostsDates;
    QTableWidget *topPostComments = ui->topPostComments;

    //lenar las publicaciones del usuario
    DoublyList *posts = appState->getPosts(); // publicaciones en general

    posts->fillTableWithTopDates(topPostDate);
    posts->fillTableWithTopPostsComments(topPostComments);



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


void userView::on_pushButton_4_clicked()
{
    ui->dateFilter->setDisplayFormat("dd/MM/yyyy");
    QString dateFilter = ui->dateFilter->text();
    qDebug() << dateFilter;
    AppState *appstate = AppState::getInstance();
    //lenar las publicaciones del usuario
    User *userlogged = appstate->getUserLogged();
    DoublyList *posts = appstate->getPosts(); // publicaciones en general
    BST *bst = new BST();

    FriendList friends = userlogged->friends;

    // filtrando las publicaciones
    posts->fillBstPosts(friends, userlogged->getEmail(), *bst);

    // mostrando las publicaciones en el scroll area
    QScrollArea *feed = ui->feed;


    bst->fillScrollAreaWithPosts(feed, dateFilter.toStdString());





}


void userView::on_pushButton_5_clicked()
{
    QString orden = ui->orden->currentText();
    QString cantidadStd = ui->cantidad->toPlainText();
    int cantidad = std::stoi(cantidadStd.toStdString());
    qDebug() << orden;
    qDebug() << cantidad;

    AppState *appstate = AppState::getInstance();
    //lenar las publicaciones del usuario
    User *userlogged = appstate->getUserLogged();
    DoublyList *posts = appstate->getPosts(); // publicaciones en general
    BST *bst = new BST();

    FriendList friends = userlogged->friends;

    // filtrando las publicaciones
    posts->fillBstPosts(friends, userlogged->getEmail(), *bst);

    // mostrando las publicaciones en el scroll area
    QScrollArea *feed = ui->feed;

    bst->fillScrollAreaOrden(feed, orden.toStdString(), cantidad);


}


void userView::on_pushButton_9_clicked()
{
    ui->bstFilter->setDisplayFormat("dd/MM/yyyy");
    QString datebst = ui->bstFilter->text();
    qDebug ()<< datebst;

    AppState *appstate = AppState::getInstance();
    //lenar las publicaciones del usuario
    User *userlogged = appstate->getUserLogged();
    DoublyList *posts = appstate->getPosts(); // publicaciones en general
    BST *bst = new BST();

    FriendList friends = userlogged->friends;

    // filtrando las publicaciones
    posts->fillBstPosts(friends, userlogged->getEmail(), *bst);

    bst->graph(datebst.toStdString());
    qDebug() << "Graficando el arbol bst";

    QLabel* imagelabel = ui->bstImage;

    QString imagePath = QDir::currentPath() + "/bst.png";

    qDebug() << imagePath;
    // Cargar la imagen en un QPixmap
    QPixmap image(imagePath);

    // Verificar si la imagen se cargó correctamente
    if (!image.isNull())
    {
        // Abrir la imagen con la aplicación predeterminada del sistema operativo
        QDesktopServices::openUrl(QUrl::fromLocalFile(imagePath));
    }
    else
    {
        imagelabel->setText("No se pudo cargar la imagen.");  // Mostrar un mensaje si no se cargó la imagen
    }


}


void userView::on_pushButton_7_clicked()
{
    AppState *appstate = AppState::getInstance();
    User *userlogged = appstate->getUserLogged();
    Avl *users = appstate->getAvlTree();

    QString newName = ui->nameInput->toPlainText();
    QString newLastname = ui->lastnameInput->toPlainText();
    QString newPassword = ui->passwordInput->toPlainText();
    QString newBirthdate = ui->birthdateInput->toPlainText();


    User* updateUser = new User(newName.toStdString(), newLastname.toStdString(),newBirthdate.toStdString(),userlogged->getEmail(),newPassword.toStdString());

    appstate->setUserLogged(updateUser);

    // actualizar usuario buscado por email
    users->buscarActualizar(userlogged->getEmail(), *updateUser);
    QMessageBox::about(this, "Actualización", "Përfil actualizado correctamente");


}


void userView::on_pushButton_8_clicked()
{
    AppState *appstate = AppState::getInstance();
    User *userlogged = appstate->getUserLogged();
    Avl *users = appstate->getAvlTree();

    users->eliminar(userlogged->getEmail());

    userlogged->setName("");
    userlogged->setLastName("");
    userlogged->setEmail("");
    userlogged->setBirthDate("");
    userlogged->setPassword("");


    MainWindow *mainw = new MainWindow();
    mainw->show();
    this->close();
}

