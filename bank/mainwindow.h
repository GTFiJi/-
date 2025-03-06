#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_qingping2_clicked();

    void on_qingping1_clicked();

    //void on_pushButton_query_clicked();

    void on_pushButton_account_clicked();

    void on_pushButton_deposit_clicked();

    void on_pushButton_withdraw_clicked();

    void on_pushButton_showaccount_clicked();

    void on_pushButton_NextMonth_clicked();

    void on_pushButton_Confirmdays_clicked();

    void on_pushButton_querymoney_clicked();

    void on_pushButton_querytime_clicked();

private:
    Ui::MainWindow *ui;
    static void process(char cmd);//处理命令
    static void read_cmd();//读取命令
    static MainWindow *koko;
    static void show_alert();
};
#endif // MAINWINDOW_H
