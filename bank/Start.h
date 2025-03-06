#ifndef START_H
#define START_H
#include "mainwindow.h"
#include <QWidget>

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:

    void on_Sign_clicked();

    void on_Login_clicked();

private:
    Ui::login *ui;
    MainWindow *s;
};

#endif // START_H
