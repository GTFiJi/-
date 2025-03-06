#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "date.h"
#include "account.h"
#include "savingaccount.h"
#include "creditaccount.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QDebug>
#include <QMessageBox>
#include <QSqlDatabase>


QString Username;
Date date(2008,11,1);//起始日期
vector<Account *> accounts;//创建动态账户数组，元素个数为0

char cmd,type;
int index_, day;
double amount, credit, rate, fee;
string user, id, desc;
Account* account;
Date date1, date2;
ofstream out;//用于添加新命令

QString account_input[5];//存放account信息，c类type,id,credit,rate,fee s类type,id, ,rate
QString change_input[3];//存放存取钱的账户名，金额，原因
int daychange;
Date time1 ,time2;
int querytype;
MainWindow *MainWindow::koko = nullptr;

// 文件存储格式
// User cmd ...

//读取命令
void MainWindow::read_cmd(){
    ifstream in;
    in.open("commands.txt");//程序启动后，逐条读出commands.txt文件中的命令，并按命令对账户进行不同的操作，将各个账户恢复到上次退出程序时的状态
    if(!in.is_open()){
        qDebug()<<"Cant find file";
        return;
    }
    while(in>>cmd){
        switch (cmd) {
        case 'a'://增加账户

            in >> user >> type >> id;
            if (type == 's') {
                in >> rate;
                account = new SavingsAccount(date, id, user ,rate);
            }
            else {
                in >> credit >> rate >> fee;
                account = new CreditAccount(date, id, user, credit, rate, fee);
            }
            accounts.push_back(account);
            break;

        case 'd'://存入现金
            in >> index_ >> amount;
            getline(in,desc);
            accounts[index_]->deposit(date, amount, desc);
            break;

        case 'w'://取出现金
            in >> index_ >> amount ;
            getline(in,desc);
            accounts[index_]->withdraw(date, amount, desc);
            break;


        case 'c'://改变日期
            in >> day;
            date = Date(date.getYear(), date.getMonth(), day);
            break;

        case 'n'://进入下个月

            if (date.getMonth() == 12)
                date = Date(date.getYear() + 1, 1, 1);//下一年1月1月
            else
                date = Date(date.getYear(), date.getMonth() + 1, 1);//下一个月1号
            for (vector<Account*>::iterator iter = accounts.begin(); iter != accounts.end(); ++iter)//遍历所有账户
                (*iter)->settle(date);//每月都有，但1月1才计算
            break;

        }
    }
    in.close();
}

struct deleter {
    template <class T> void operator () (T* p) { delete p; }
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    koko = this;//另外设置的新内部地址，ui是内部的所以是必需的
    //初始语
    QString theHello = "欢迎用户"+ Username;
    ui->label_chushi->setText(theHello);
    //读取文件
    read_cmd();
    //显示需处理信息，还款的提示，当月账户的统计
    show_alert();

    out.open("commands.txt",ios::app);//开始处理新命令并把新命令添加到commands.txt文件中
}


MainWindow::~MainWindow()
{
    delete ui;
}

//处理命令
void MainWindow::process(char cmd){

    date.show();
    qDebug() << "\tTotal:" << Account::getTotal() << "\tcommand>";

    switch (cmd) {
    case 'a'://增加账户
        try{
            // cin >> type >> id;
            type = account_input[0].toStdString().c_str()[0];
            user = Username.toStdString();
            id = account_input[1].toStdString();//新账户名
            qDebug()<<"ok3";

            if(type == 's' || type == 'c'){
                out << endl << cmd << " " << user << " ";
                out << type << " " << id << " ";
            }
            else throw runtime_error("账户类型错误");
        }
        catch (runtime_error& err) {
            //QMessageBox::warning(this,tr("警告"),tr(err.what());
            qDebug()<<"a:runtime" << err.what() ;
        }

        if (type == 's') {
            // 存入rate;
            rate = account_input[3].toDouble();
            out<<rate;
            account = new SavingsAccount(date, id, user, rate);
        }
        else {
            // 存入credit信用额，rate，fee;
            credit = account_input[2].toDouble();
            rate = account_input[3].toDouble();
            fee = account_input[4].toDouble();
            out<<credit<<" "<<rate<<" "<<fee;
            account = new CreditAccount(date, id, user, credit, rate, fee);
            qDebug()<<"ok4";
        }
        qDebug()<<"here\n";

        koko->ui->textBrowser_output->append(Username+ "的"+ QString::fromStdString(id)+ "账号已创建.");
        qDebug()<<"ok5";
        accounts.push_back(account);

        break;

    case 'd'://存入现金
        try{
            // cin >> index_ >> amount;由QString转换
            index_ = change_input[0].toInt();
            amount = change_input[1].toDouble();
            desc = change_input[2].toStdString();
            //deposit里其实已经检测过了，双重
            if(index_ < 0 || index_ >= accounts.size()){
                throw runtime_error("The index you input is not exist.");
            }
            accounts[index_]->deposit(date, amount, desc);

            out << endl << cmd << " " ;
            out<<index_<<" "<<amount<<" ";
            out<<desc;
            show_alert();

            if(accounts[index_]->getUser() == Username.toStdString()){ // 用户过滤
                koko->ui->textBrowser_output->append(QString::fromStdString(to_string(date.getYear())+"年"+to_string(date.getMonth())+"月"+to_string(date.getDay())+"日"+accounts[index_]->getId()+"存了"+to_string(amount)+"元,原因："+desc));
            }
        }
        catch (runtime_error& err) {
            qDebug()<<"d:runtime" << err.what();
        }

        break;

    case 'w'://取出现金

        try{
            //cin >> index_ >> amount;
            index_ = change_input[0].toInt();
            amount = change_input[1].toDouble();
            desc = change_input[2].toStdString();

            getline(cin, desc);
            //QT中不存在抛出这个异常了前面deposit已经检测过了
            if(index_ < 0 || index_ >= accounts.size()){
                throw runtime_error("The index you input is not exist.");
            }
            accounts[index_]->withdraw(date, amount, desc);

            out << endl << cmd << " ";
            out<<index_<<" "<<amount<<" ";
            out<<desc;
            show_alert();
            if(accounts[index_]->getUser() == Username.toStdString()){ // 用户过滤
                koko->ui->textBrowser_output->append(QString::fromStdString(to_string(date.getYear())+"年"+to_string(date.getMonth())+"月"+to_string(date.getDay())+"日"+accounts[index_]->getId()+"取了"+to_string(amount)+"元,原因："+desc));
            }
        }
        //处理AccountException信息（异常）
        catch (AccountException& err){//
            qDebug() <<"w:AccountException" << err.what() ;
            QMessageBox::warning(koko,tr("警告信息"),tr("没钱了"));
        }
        catch (runtime_error& err) {
            qDebug()<<"w:runtime_err" << err.what() ;
        }

        break;

    case 's'://查询各账户信息
        static unsigned int num;
        num = 1;
        for (size_t i = 0; i < accounts.size(); i++) {

            //cout << "[" << i << "] ";
            accounts[i]->show();
            //cout << endl;

            if(accounts[i]->getUser() == Username.toStdString()) // 用户过滤
                if(accounts[i]->s_c())
                {
                    koko->ui->textBrowser_output->append(QString::fromStdString("[" + to_string(num++) + "] " +"类型:credit  账户名：" +accounts[i]->show()));
                }
                if(!accounts[i]->s_c())
                {
                    koko->ui->textBrowser_output->append(QString::fromStdString("[" + to_string(num++) + "] " +"类型:saving  账户名：" +accounts[i]->show()));
                }
        }

        break;

    case 'c'://改变日期

        //cin >> day;
        day = daychange;

        if (day < date.getDay())
        {
            qDebug() << "You cannot specify a previous day";//日子已经过了
            QMessageBox::warning(koko,tr("警告信息"),tr("听反方向的钟也回不去过去qwq"));
                    show_alert();
            break;
        }
        else if (day > date.getMaxDay() || day<1)
            {
            qDebug() << "Invalid day";
            QMessageBox::warning(koko,tr("警告信息"),tr("无效日"));
                    show_alert();
            break;//终止，防止写入
            }
        else
            date = Date(date.getYear(), date.getMonth(), day);
        show_alert();

        out << endl << cmd << " ";
        out<<day;
        break;

    case 'n'://进入下个月

        if (date.getMonth() == 12)
            date = Date(date.getYear() + 1, 1, 1);//下一年1月1月
        else
            date = Date(date.getYear(), date.getMonth() + 1, 1);//下一个月1号

        for (vector<Account*>::iterator iter = accounts.begin(); iter != accounts.end(); ++iter)
            (*iter)->settle(date);
        show_alert();
        out << endl << cmd << " ";
        break;

    case 'q'://查询一段时间内的账目
        try{
            date1 = time1;
            date2 = time2;
            //Account::query(date1, date2 ,user);
            koko->ui->textBrowser_output->append(QString::fromStdString(Account::query(date1, date2, Username.toStdString(),querytype)));
        }
        //利用QT的日期所以其实并不会有这个DateException的异常（应该）
        catch (DateException & err){
            qDebug()<<"q:DataException" << err.what();
            if(cin.fail()) cin.clear();
        }
    }
}

void MainWindow::show_alert(){
    double debt = 0;
    double income = 0, cost = 0;
    double debting;
    QString datenowdays = QString("当前日期 年: %1, 月: %2, 日: %3")
                              .arg(date.getYear())
                              .arg(date.getMonth())
                              .arg(date.getDay());
    koko->ui->textBrowser_nowdate->setText("");
    koko->ui->textBrowser_nowdate->append(datenowdays);
    for(unsigned int i=0; i < accounts.size(); i++){
        if(accounts[i]->getUser() == Username.toStdString()){
            if(accounts[i]->s_c())
            {//指回来类型信用卡c  1
                debting=accounts[i]->get_debt();
                if(debting<0)
                {
                    debt -= accounts[i]->get_debt();
                }
            }
        }
    }
    //cout << date.getYear()<<date.getMonth()-1<<1
    income = Account::month_income(Date(date.getYear(),date.getMonth(),1),Date(date.getYear(),date.getMonth(),date.getMaxDay()),Username.toStdString());//收入
    cost = Account::month_cost(Date(date.getYear(),date.getMonth(),1),Date(date.getYear(),date.getMonth(),date.getMaxDay()),Username.toStdString());//支出
    koko->ui->textBrowser_account->append(QString::fromStdString("本月应还："+to_string(debt)+" 本月收入："+to_string(income)+" 本月支出"+to_string(cost)));
}

void MainWindow::on_qingping2_clicked()
{
    koko->ui->textBrowser_output->setText("");
}


void MainWindow::on_qingping1_clicked()
{
  koko->ui->textBrowser_account->setText("");
}

/*
void MainWindow::on_pushButton_query_clicked()
{
    querytype=0;
    time1 = Date(ui->dateEdit1->date().year(), ui->dateEdit1->date().month(), ui->dateEdit1->date().day());
    time2 = Date(ui->dateEdit2->date().year(), ui->dateEdit2->date().month(), ui->dateEdit2->date().day());
    MainWindow::process('q');
}
*/


void MainWindow::on_pushButton_account_clicked()
{
    account_input[1] = ui->lineEdit_ID->text();
    for(auto &iter : accounts){
        if(iter->getId() == account_input[1].toStdString()){
            QMessageBox::warning(this,tr("警告信息"),tr("系统中已有重名账号"));
            return;
        }
    }
    if(ui->checkBox_S->isChecked() && !ui->checkBox_C->isChecked()){
        account_input[0]='s';
    }
    else if(!ui->checkBox_S->isChecked() && ui->checkBox_C->isChecked()){
        account_input[0]='c';
    }
    else{
        QMessageBox::warning(this,tr("警告"),tr("请选择一种账户"));
        return;
    }
    account_input[2] = ui->lineEdit_credit->text();
    account_input[3] = ui->lineEdit_rate->text();
    account_input[4] = ui->lineEdit_fee->text();
    qDebug()<<"ok1";
    MainWindow::process('a');
    qDebug()<<"ok2";
}


void MainWindow::on_pushButton_deposit_clicked()
{
    change_input[0] = ui->lineEdit_DepositID->text();
    for(unsigned int i=0; i < accounts.size(); i++){
        if(accounts[i]->getId() == change_input[0].toStdString()){
            if(accounts[i]->getUser() != Username.toStdString()){
                QMessageBox::warning(this,tr("警告"),tr("这不是你的账号,请不要乱动666"));
                return;
            }
            change_input[0] = (char)(i+48);
            change_input[1] = ui->lineEdit_Depositamount->text();
            change_input[2] = ui->lineEdit_Depositdesc->text();
            MainWindow::process('d');
            return;
        }
    }
    QMessageBox::warning(this,tr("警告"),tr("找不到该账号haha"));
}


void MainWindow::on_pushButton_withdraw_clicked()
{
    change_input[0] = ui->lineEdit_WithdrawID->text();
    for(unsigned int i=0; i < accounts.size(); i++)
    {//遍历所有对id
        if(accounts[i]->getId() == change_input[0].toStdString()){
            if(accounts[i]->getUser() != Username.toStdString()){
                QMessageBox::warning(this,tr("警告"),tr("这不是你的账号,请不要乱动666"));
                return;
            }
            change_input[0] = (char)(i+48);
            change_input[1] = ui->lineEdit_Withdrawamount->text();
            change_input[2] = ui->lineEdit_Withdrawdesc->text();
            MainWindow::process('w');
            return;
        }
    }
    QMessageBox::warning(this,tr("警告"),tr("找不到该账号haha"));
}


void MainWindow::on_pushButton_showaccount_clicked()
{
     MainWindow::process('s');
}


void MainWindow::on_pushButton_NextMonth_clicked()
{
    MainWindow::process('n');
}


void MainWindow::on_pushButton_Confirmdays_clicked()
{
    koko->ui->textBrowser_nowdate->clear();
    daychange = koko->ui->lineEditday->text().toInt();
    if(daychange || (daychange==0))
        MainWindow::process('c');
    else
        QMessageBox::warning(this,tr("警告"),tr("需输入天数"));
    //输出当前日期
    /*QString datenowdays = QString("当前日期 年: %1, 月: %2, 日: %3")
                          .arg(date.getYear())
                          .arg(date.getMonth())
                          .arg(date.getDay());
    koko->ui->textBrowser_nowdate->append(datenowdays);
*/
}


void MainWindow::on_pushButton_querymoney_clicked()
{
    querytype=1;
    time1 = Date(ui->dateEdit1->date().year(), ui->dateEdit1->date().month(), ui->dateEdit1->date().day());
    time2 = Date(ui->dateEdit2->date().year(), ui->dateEdit2->date().month(), ui->dateEdit2->date().day());
    MainWindow::process('q');
}


void MainWindow::on_pushButton_querytime_clicked()
{
    querytype=0;
    time1 = Date(ui->dateEdit1->date().year(), ui->dateEdit1->date().month(), ui->dateEdit1->date().day());
    time2 = Date(ui->dateEdit2->date().year(), ui->dateEdit2->date().month(), ui->dateEdit2->date().day());
    MainWindow::process('q');
}

