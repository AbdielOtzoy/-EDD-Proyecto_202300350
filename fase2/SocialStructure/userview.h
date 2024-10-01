#ifndef USERVIEW_H
#define USERVIEW_H

#include <QWidget>

namespace Ui {
class userView;
}

class userView : public QWidget
{
    Q_OBJECT

public:
    explicit userView(QWidget *parent = nullptr);
    ~userView();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void on_tabWidget_currentChanged(int index);

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::userView *ui;
};

#endif // USERVIEW_H
