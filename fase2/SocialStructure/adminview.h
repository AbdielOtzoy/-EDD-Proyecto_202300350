#ifndef ADMINVIEW_H
#define ADMINVIEW_H

#include <QWidget>

namespace Ui {
class AdminView;
}

class AdminView : public QWidget
{
    Q_OBJECT

public:
    explicit AdminView(QWidget *parent = nullptr);
    ~AdminView();

private slots:
    void on_pushButton_clicked();

private:
    Ui::AdminView *ui;
};

#endif // ADMINVIEW_H
