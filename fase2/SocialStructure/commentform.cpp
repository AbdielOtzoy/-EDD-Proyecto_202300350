#include "commentform.h"
#include "ui_commentform.h"
#include <QDebug>
#include "models/comment.h"
#include "structures/bst.h"
#include <ctime>
#include "appstage.h"
#include "user.h"
#include "structures/doublylist.h"

// Modificar el constructor para almacenar un puntero a Post
CommentForm::CommentForm(Post* post, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CommentForm)
    , post(post)  // Inicializar el puntero a Post
{
    ui->setupUi(this);
}

CommentForm::~CommentForm()
{
    delete ui;
}

void CommentForm::on_pushButton_clicked()
{
    QString content = ui->content->toPlainText();
    // Obtener el usuario actual desde el estado de la aplicación
    AppState *appState = AppState::getInstance();
    User *userlogged = appState->getUserLogged();
    DoublyList *posts = appState->getPosts();

    qDebug() << "nomas";


    // Obtener la fecha y hora actual
    time_t now = time(0);
    tm *ltm = localtime(&now);
    std::string date = std::to_string(1 + ltm->tm_mday) + "-" + std::to_string(1 + ltm->tm_mon) + "-" + std::to_string(1900 + ltm->tm_year);
    std::string time = std::to_string(1 + ltm->tm_hour) + ":" + std::to_string(1 + ltm->tm_min) + ":" + std::to_string(1 + ltm->tm_sec);

    // Crear un nuevo comentario
    Comment* newComment = new Comment(userlogged->getEmail(), content.toStdString(), date, time);

    // Insertar el nuevo comentario en el Post (modificando el Post original a través del puntero)
    post->comments.insert(*newComment);

    posts->insertCommentByContent(post->getContent(), *newComment);


    // Cerrar la ventana de comentarios
    this->close();
}
