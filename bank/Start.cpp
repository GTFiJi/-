#include "Start.h"
#include "ui_Start.h"
#include "mainwindow.h"
#include <QMovie>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlTableModel>
#define  endl '\n'
extern QString Username;//登录时的用户名
login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}
//注册
void login::on_Sign_clicked()
{
    QString username = this->ui->lineEdit_loginusername->text();
    QString passwordfirst = this->ui->lineEdit_loginpassword1->text();
    QString passwordsecond = this->ui->lineEdit_loginpassword2->text();
    // 检查用户名是否存在
    QString checkCmd = QString("SELECT COUNT(*) FROM userinfo WHERE username='%1'").arg(username);
    QSqlQuery checkQuery;
    if (checkQuery.exec(checkCmd))
    {
        checkQuery.next();
        int count = checkQuery.value(0).toInt();//用户名计数，查询结果中的第一个字段，满足条件的行数，转为整数
        if (count > 0)
        {
            qDebug() << "用户名已存在" << endl;
            // 提示
            QMessageBox::warning(this, "注册失败", "用户名已存在，请选择其他用户名。");
            return;
        }
    }
    else
    {
        qDebug() << "检查用户名失败" << endl;
        return;
    }

    // 插入新用户信息
    if(passwordfirst==passwordsecond)
    {
    QString insertCmd = QString("INSERT INTO userinfo (username, password) VALUES ('%1', '%2')").arg(username).arg(passwordfirst);
    QSqlQuery insertQuery;
    if (insertQuery.exec(insertCmd))
    {
        qDebug() << "插入成功" << endl;
        QMessageBox::information(this, "注册成功", "账号创建成功！");
    }
    else
    {
        qDebug() << "插入失败" << endl;
        QMessageBox::warning(this, "注册失败", "账号创建失败，请重试。");
    }
    }
    else
    {
        QMessageBox::warning(this, "注册失败", "两次密码不一样，请重试。");
    }
}
//注册
void login::on_Login_clicked()
{
    QString username = this->ui->lineEdit_username->text();
    QString password = this->ui->lineEdit_password->text();
    //创建model
    QSqlTableModel *model = new QSqlTableModel;
    //绑定表
    model->setTable("userinfo");//main.cpp中已有说明
    //过滤数据
    model->setFilter(QString("username='%1' and password='%2'").arg(username).arg(password));
    //查询
    model->select();
    //结果
    int row = model->rowCount();
    Username = username;
    s = new MainWindow;
    if(row>0){
        qDebug()<<"登录成功"<<endl;
        //打开主界面
        s->show();
    }
    else{
        QMessageBox::about(NULL,"","用户名或密码错误");
        s->deleteLater();
        qDebug()<<"登录失败"<<endl;
    }

}

