#ifndef COMMENTFORM_H
#define COMMENTFORM_H

#include <QWidget>
#include "models/post.h"

namespace Ui {
class CommentForm;
}

class CommentForm : public QWidget
{
    Q_OBJECT

public:
    // Modificar el constructor para recibir un puntero a Post
    explicit CommentForm(Post* post, QWidget *parent = nullptr);
    ~CommentForm();

private slots:
    void on_pushButton_clicked();

private:
    Ui::CommentForm *ui;
    Post* post;  // Apuntador a Post, para modificar la publicación original
};

#endif // COMMENTFORM_H
