#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "string"
using std::string;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_Button1_clicked();

    void on_Button_2_clicked();


    void on_textBrowser_anchorClicked(const QUrl &arg1);

private:
    Ui::MainWindow *ui;
};

class SearchInfo
{
private:
    string LINE;
    //当前行的内容
    int BOOKNAME;
    //书名的序号
    int PAGE;
    //页数
    int CHAPTER;
    //章节
public:
    SearchInfo(int BOOKNAME, int PAGE, int CHAPTER, string LINE);
    ~SearchInfo();
    string getLine();
};

#endif // MAINWINDOW_H
