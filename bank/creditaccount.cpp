//creditaccount.cpp
#include "creditaccount.h"
#include <string>

using namespace std;

CreditAccount::CreditAccount(const Date &date, string id,string user, double credite, double rate, double fee)
: Account(date,id,user),acc(date,0),credit(credite),rate(rate),fee(fee) {} //对父类，以及类对象初始化


//完成对类的，展示内容

// 信用账户存钱操作
void CreditAccount::deposit(Date &date, double amount, string desc){

    //cout<<getBalance()<<endl;
    record(date,amount,desc);
    acc.change(date,getBalance());

}

//信用账户取钱操作

//结算利息
void CreditAccount::settle(Date &date) {
    acc.change(date,getBalance());
    interest=acc.getSum(date)*rate; //计算利息
    //rate为日利率，按日欠款计息，日累积乘以日利率即利息

    if(date.getMonth()==1 && date.getDay()==1){
        record(date,interest,"interest");//在余额中加上利息
        record(date,-fee,"annual fee");//1月1交年费
    
    }
    else{
        record(date,interest,"interest");//在余额中加上利息
    }
    interest=0;
    acc.reset(date,getBalance());
}

//取钱操作需要与信用额度对比
void CreditAccount::withdraw(Date &date, double amount, string desc) {

    if(credit+getBalance()>=amount){
        record(date,-amount,desc);
        acc.change(date,getBalance());
    }
    else{
        throw AccountException(this);//在AccoutException中保存一个保存Account型常指针，指向发生错误的账户
    }
}

string CreditAccount::show() const {        //子类需要重写
    return  getId() + "\tBalance: " + to_string(getBalance()) + "\t" + "Available credit:" + to_string(credit + getBalance());

}
