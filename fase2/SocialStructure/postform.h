#ifndef POSTFORM_H
#define POSTFORM_H

#include <QWidget>

namespace Ui {
class PostForm;
}

class PostForm : public QWidget
{
    Q_OBJECT

public:
    explicit PostForm(QWidget *parent = nullptr);
    ~PostForm();

private slots:
    void on_pushButton_clicked();

private:
    Ui::PostForm *ui;
};

#endif // POSTFORM_H
