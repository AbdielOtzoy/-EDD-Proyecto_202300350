#include "register.h"
#include "ui_register.h"
#include "mainwindow.h"
#include "user.h"
#include "appstage.h"
#include <QDebug>
#include <QMessageBox>

Avl *avl = new Avl();

Register::Register(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Register)
{
    ui->setupUi(this);
}

Register::~Register()
{
    delete ui;
}

void Register::on_pushButton_2_clicked()
{
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
    this->close();
}


void Register::on_pushButton_clicked()
{
    Avl *avlTree = AppState::getInstance()->getAvlTree();

    QString name = ui->name->toPlainText();
    QString lastname = ui->lastname->toPlainText();
    QString birthday = ui->birthday->text();
    QString email = ui->email->toPlainText();
    QString password = ui->password->toPlainText();

    if(name != "" && lastname != "" && birthday != "" && email != "" && password != "") {
        User *user = new User(name.toStdString(), lastname.toStdString(), birthday.toStdString(), email.toStdString(), password.toStdString());
        user->printUser();

        avlTree->agregar(*user);
        QMessageBox::about(this, "succes","Se ha registrado exitosamente");
    } else {
        QMessageBox::warning(this, "error","Llenar todos los datos");

    }

    }


