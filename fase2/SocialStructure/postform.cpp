#include "postform.h"
#include "user.h"
#include "models/post.h"
#include "structures/doublylist.h"
#include "appstage.h"
#include <QMessageBox>
#include "ui_postform.h"
#include <QDebug>
#include <ctime>
#include "userview.h"

PostForm::PostForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PostForm)
{
    ui->setupUi(this);
}

PostForm::~PostForm()
{
    delete ui;
}

void PostForm::on_pushButton_clicked()
{
    AppState *appstate = AppState::getInstance();
    QString content = ui->content->toPlainText();
    User *userLogged = appstate->getUserLogged();
    DoublyList* posts = appstate->getPosts();

    if(content != "") {

        // obtener la fecha y hora actual
        time_t now = time(0);
        tm *ltm = localtime(&now);
        string date = to_string(1 + ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year);
        string time = to_string(1 + ltm->tm_hour) + ":" + to_string(1 + ltm->tm_min) + ":" + to_string(1 + ltm->tm_sec);

        Post* newPost = new Post(userLogged->getEmail(), content.toStdString(), date, time);

        newPost->printPost();

        appstate->agregarPost(newPost);

        QMessageBox::about(this, "succes", "se ha creado la publicación correctamente");

        userView *userview = new userView();

        userview->show();
        this->close();


    } else {
        QMessageBox::warning(this, "error", "Debes de añadir una descripción a la publiación");
    }
}

