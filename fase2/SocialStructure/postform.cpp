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
#include <iomanip> // Para std::setw y std::setfill
#include <sstream> // Para std::ostringstream

using namespace std;

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

    if(content != "") {

        // obtener la fecha y hora actual
        time_t now = time(0);
        tm *ltm = localtime(&now);

        // Crear el stringstream para formatear la fecha
        ostringstream dateStream;

        // Asegurarse de que siempre tenga 2 dígitos para día y mes, y 4 para el año
        dateStream << setw(2) << setfill('0') << ltm->tm_mday << "/"
                   << setw(2) << setfill('0') << (1 + ltm->tm_mon) << "/"
                   << setw(4) << (1900 + ltm->tm_year);

        // Extraer la fecha formateada
        string date = dateStream.str();

        // Crear el stringstream para formatear la hora
        ostringstream timeStream;

        // Asegurarse de que siempre tenga 2 dígitos para horas, minutos y segundos
        timeStream << setw(2) << setfill('0') << ltm->tm_hour << ":"
                   << setw(2) << setfill('0') << ltm->tm_min << ":"
                   << setw(2) << setfill('0') << ltm->tm_sec;

        // Extraer la hora formateada
        string time = timeStream.str();

        // Imprimir los resultados
        cout << "Fecha: " << date << endl;
        cout << "Hora: " << time << endl;
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

