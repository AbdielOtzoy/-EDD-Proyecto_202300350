#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include "register.h"
#include "userview.h"
#include <QMessageBox>
#include "adminview.h"
#include "appstage.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    AppState *appState = AppState::getInstance();
    Avl *avlTree = appState->getAvlTree();
    User *userLogged = appState->getUserLogged();
    QString user = ui->user->toPlainText();
    QString password = ui->password->toPlainText();



    if(user != "" && password != "") {
        if(user =="admin@gmail.com" && password == "EDD2S2024") {
            qDebug() << "admin";
            AdminView *adminView= new AdminView();
            adminView->show();
            this->close();
        } else {
            qDebug() << "user";
            avlTree->ver();
            Nodo userFound = avlTree->buscar(user.toStdString());
            if(userFound != NULL) {
                if(password.toStdString() == userFound->data.getPassword()) {
                    User userLog = userFound->data;

                    userLogged->setName(userLog.getName());
                    userLogged->setLastName(userLog.getLastName());
                    userLogged->setBirthDate(userLog.getBirthDate());
                    userLogged->setEmail(userLog.getEmail());
                    userLogged->setPassword(userLog.getPassword());
                    userLogged->friends = userLog.friends;
                    userLogged->requestsReceived = userLog.requestsReceived;
                    userLogged->requestsSent = userLog.requestsSent;

                    userLogged->printUser();

                    appState->setUserLogged(userLogged);

                    userView *userview = new userView();
                    userview->show();
                    this->close();
                } else {
                    QMessageBox::warning(this, "error","contraseña incorrecta");
                }

            } else {
                QMessageBox::warning(this, "error","No se ha encontrado el usuario");
            }

        }
    } else {
        QMessageBox::warning(this, "error","no pueden haber campos vacios");



    }
}


void MainWindow::on_pushButton_2_clicked()
{   
    Register *registerWindow = new Register();
    registerWindow->show();  // Mostrar la ventana secundaria
    this->close();  // Ocultar la ventana principal si es necesario
}

