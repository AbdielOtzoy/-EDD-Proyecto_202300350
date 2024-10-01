#include "adminview.h"
#include "ui_adminview.h"
#include "mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>
#include "appstage.h"
#include "structures/avl.h"
#include "user.h"
#include <QPixmap>
#include <QDir>
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>
#include "models/request.h"
#include "models/post.h"
#include "models/comment.h"
#include "structures/doublylist.h"

using json = nlohmann::json;

AdminView::AdminView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AdminView)
{
    ui->setupUi(this);
}

AdminView::~AdminView()
{
    delete ui;
}

void AdminView::on_pushButton_clicked()
{
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
    this->close();
}


void AdminView::on_pushButton_4_clicked()
{
    AppState *appstate = AppState::getInstance();
    // Mostrar el explorador de archivos y filtrar para archivos .json
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Seleccionar archivo JSON",
                                                    "", // Directorio inicial vacío, puedes poner una ruta predeterminada
                                                    "Archivos JSON (*.json)");

    if (!fileName.isEmpty()) {
        // Si se seleccionó un archivo, se intenta abrir
        std::ifstream jsonFile(fileName.toStdString());

        if (jsonFile.is_open()) {
            try {
                // Cargar el archivo JSON
                json jsonData;
                jsonFile >> jsonData;

                // Verificar si el JSON es un array
                if (jsonData.is_array()) {
                    // Recorrer el array de objetos y mostrar la información
                    Avl *users = appstate->getAvlTree();
                    for (const auto& item : jsonData) {
                        std::string nombres =  item["nombres"];
                        std::string apellidos = item["apellidos"];
                        std::string fecha_de_nacimiento = item["fecha_de_nacimiento"];
                        std::string correo = item["correo"];
                        std::string password = item["contraseña"];

                        qDebug() << nombres;
                        qDebug() << apellidos;
                        qDebug() << fecha_de_nacimiento;
                        qDebug() << correo;
                        qDebug() << password;
                        // crear el objeto user e insertarlo e insertarlo en appstate
                        User* user = new User(nombres, apellidos, fecha_de_nacimiento, correo, password);

                        users->agregar(*user);
                        qDebug() << "usuario agregado correctaemene";
                        qDebug() << "-----------------------------------";


                    }
                }
            } catch (const std::exception &e) {
                qDebug() << "Error al analizar el archivo JSON:" << e.what();
            }
            jsonFile.close();
        } else {
            qDebug() << "No se pudo abrir el archivo.";
        }
    }
}


void AdminView::on_pushButton_8_clicked()
{
    // reporte para el arbol de usuarios
    AppState *appstate = AppState::getInstance();
    Avl *users = appstate->getAvlTree();

    users->graficarDot();

    QLabel* avlImg = ui->avlImage;
    QString imagePath = QDir::currentPath() + "/Avl.png";

    qDebug() << imagePath;
    // Cargar la imagen en un QPixmap
    QPixmap image(imagePath);

    // Verificar si la imagen se cargó correctamente
    if (!image.isNull())
    {
        // Ajustar la imagen al QLabel, manteniendo la relación de aspecto original
        avlImg->setPixmap(image.scaled(avlImg->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

        // Abrir la imagen con la aplicación predeterminada del sistema operativo
        QDesktopServices::openUrl(QUrl::fromLocalFile(imagePath));
    }
    else
    {
        avlImg->setText("rNo se pudo cargar la imagen.");  // Mostrar un mensaje si no se cargó la imagen
    }
}


void AdminView::on_pushButton_7_clicked()
{
    AppState *appstate = AppState::getInstance();
    // Mostrar el explorador de archivos y filtrar para archivos .json
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Seleccionar archivo JSON",
                                                    "", // Directorio inicial vacío, puedes poner una ruta predeterminada
                                                    "Archivos JSON (*.json)");
    // Recorrer el array de objetos y mostrar la información
    Avl *users = appstate->getAvlTree();
    if (!fileName.isEmpty()) {
        // Si se seleccionó un archivo, se intenta abrir
        std::ifstream jsonFile(fileName.toStdString());

        if (jsonFile.is_open()) {
            try {
                // Cargar el archivo JSON
                json jsonData;
                jsonFile >> jsonData;

                // Verificar si el JSON es un array
                if (jsonData.is_array()) {

                    for (const auto& item : jsonData) {
                        std::string receptor =  item["receptor"];
                        std::string emisor = item["emisor"];
                        std::string estado = item["estado"];

                        qDebug() << "receptor: " << receptor;
                        qDebug() << "emisor: " << emisor;
                        qDebug() << "estado: " << estado;

                        Request* request = new Request(emisor, receptor, estado);
                        users->procesarRequest(request);

                    }
                }
            } catch (const std::exception &e) {
                qDebug() << "Error al analizar el archivo JSON:" << e.what();
            }
            jsonFile.close();
        } else {
            qDebug() << "No se pudo abrir el archivo.";
        }
    }
}


void AdminView::on_pushButton_6_clicked()
{
    AppState *appstate = AppState::getInstance();
    // Mostrar el explorador de archivos y filtrar para archivos .json
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Seleccionar archivo JSON",
                                                    "", // Directorio inicial vacío, puedes poner una ruta predeterminada
                                                    "Archivos JSON (*.json)");
    DoublyList *posts = appstate->getPosts();
    if (!fileName.isEmpty()) {
        // Si se seleccionó un archivo, se intenta abrir
        std::ifstream jsonFile(fileName.toStdString());

        if (jsonFile.is_open()) {
            try {
                // Cargar el archivo JSON
                json jsonData;
                jsonFile >> jsonData;

                // Verificar si el JSON es un array
                if (jsonData.is_array()) {

                    for (const auto& item : jsonData) {
                        std::string correo =  item["correo"];
                        std::string contenido = item["contenido"];
                        std::string fecha = item["fecha"];
                        std::string hora = item["hora"];

                        qDebug() << "correo: " << correo;
                        qDebug() << "contenido: " << contenido;
                        qDebug() << "fecha: " << fecha;
                        qDebug() << "hora: " << hora;

                        Post *newPost = new Post(correo,contenido,fecha, hora);

                        if(item.contains("comentarios")) {
                            qDebug() << "Comentarios";
                            for(const auto& comentario : item["comentarios"]) {
                                std::string correo_comentario = comentario["correo"];
                                std::string texto_comentario = comentario["comentario"];
                                std::string fecha_comentario = comentario["fecha"];
                                std::string hora_comentario = comentario["hora"];

                                qDebug() << "- Comentario de: " << correo_comentario;
                                qDebug() << "  " << texto_comentario;
                                qDebug() << "  Fecha: " << fecha_comentario << " Hora: " << hora_comentario;
                                Comment *newComment = new Comment(correo_comentario, texto_comentario, fecha_comentario, hora_comentario);
                                newPost->comments.insert(*newComment);
                            }
                        }

                        posts->addNode(*newPost);


                    }
                }
            } catch (const std::exception &e) {
                qDebug() << "Error al analizar el archivo JSON:" << e.what();
            }
            jsonFile.close();
        } else {
            qDebug() << "No se pudo abrir el archivo.";
        }
    }
}


void AdminView::on_pushButton_9_clicked()
{
    // generar reporte de publicaciones
    AppState *appstate = AppState::getInstance();
    DoublyList *posts = appstate->getPosts();

    posts->createDotFile();

    QLabel* postsImage = ui->postsImage;
    QString imagePath = QDir::currentPath() + "/posts.png";

    qDebug() << imagePath;
    // Cargar la imagen en un QPixmap
    QPixmap image(imagePath);

    // Verificar si la imagen se cargó correctamente
    if (!image.isNull())
    {
        // Ajustar la imagen al QLabel, manteniendo la relación de aspecto original
        postsImage->setPixmap(image.scaled(postsImage->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        // Abrir la imagen con la aplicación predeterminada del sistema operativo
        QDesktopServices::openUrl(QUrl::fromLocalFile(imagePath));
    }
    else
    {
        postsImage->setText("rNo se pudo cargar la imagen.");  // Mostrar un mensaje si no se cargó la imagen
    }
}


void AdminView::on_pushButton_5_clicked()
{
    // llenar la tabla dependiendo el orden escogido
    QString orden = ui->orden->currentText();
    qDebug() << "orden escogido:" << orden;

    QTableWidget *tableUsers = ui->usuarios;

    // limpiar la tabla de usuarios
    tableUsers->clear();
    tableUsers->setRowCount(0);
    tableUsers->setHorizontalHeaderLabels(QStringList() << "Nombres" << "Apellidos" << "Correo" << "Nacimiento" << "Eliminar" << "Modificar");

    // obtener los datos globales de los usuarios
    AppState *appstate = AppState::getInstance();
    Avl *users = appstate->getAvlTree();

    users->fillUsersTableWithOrden(tableUsers, orden.toStdString());

}


void AdminView::on_pushButton_2_clicked()
{
    // buscar el usuario
    QString userToSearch = ui->usertoSearch->toPlainText();

    // obtener los datos globales de los usuarios
    AppState *appstate = AppState::getInstance();
    Avl *users = appstate->getAvlTree();

    Nodo userFound = users->buscar(userToSearch.toStdString());

    if(userFound == NULL) {
        QMessageBox::warning(this, "Usuario no encontrado","El usuario buscado no existe");
    }
    if(userFound != NULL) {
        QTableWidget *tableUsers = ui->usuarios;

        // limpiar la tabla de usuarios
        tableUsers->clear();
        tableUsers->setRowCount(0);
        tableUsers->setHorizontalHeaderLabels(QStringList() << "Nombres" << "Apellidos" << "Correo" << "Nacimiento" << "Eliminar" << "Modificar");

        int row = tableUsers->rowCount(); // Obtiene el número actual de filas
        tableUsers->insertRow(row); // Inserta una nueva fila al final de la tabla

        // Agrega los datos a cada celda de la fila
        tableUsers->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(userFound->data.getName())));
        tableUsers->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(userFound->data.getLastName())));
        tableUsers->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(userFound->data.getEmail())));
        tableUsers->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(userFound->data.getBirthDate())));

        QPushButton* modifyBtn = new QPushButton("Modificar");
        QPushButton* deleteBtn = new QPushButton("Eliminar");

        QObject::connect(modifyBtn, &QPushButton::clicked, [tableUsers, row](){
            qDebug() << "Modificando usuario";
        });

        QObject::connect(deleteBtn, &QPushButton::clicked, [this, userFound, users](){
            users->eliminar(userFound->data.getEmail());
            qDebug() << "Eliminando el usuario: " << userFound->data.getEmail();
        });
        tableUsers->setCellWidget(row, 4, modifyBtn);
        tableUsers->setCellWidget(row, 5, deleteBtn);




    }
}

