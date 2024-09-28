#include "adminview.h"
#include "ui_adminview.h"
#include "mainwindow.h"

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

