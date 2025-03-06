#include "Start.h"
#include <QApplication>
#include <QString>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlDatabase>

#define endl '\n'

int main(int argc, char *argv[])
{
    // 创建QApplication实例
    QApplication a(argc, argv);

    // 创建数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    // 设置数据库名字
    db.setDatabaseName("login.db");
    // 打开数据库
    if(db.open())
    {
        qDebug() << "已打开数据库" << endl;
    }
    else
    {
        qDebug() << "未打开数据库" << endl;
    }

    // 创建一个存储username和password的的数据库表,表名userinfo已有则不创建
    QString cmd = "create table if not exists userinfo(username varchar(64),password varchar(64))";

    // 执行sql语句
    QSqlQuery query;
    if(query.exec(cmd))
    {
        qDebug() << "execute success" << endl;
    }
    else
    {
        qDebug() << "execute failure" << endl;
    }

    login login11;
    // 打开登录界面
    login11.show();
    return a.exec();
}
