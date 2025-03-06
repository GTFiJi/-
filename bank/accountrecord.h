//accountrecord.h
#ifndef __ACCOUNT_RECORD__
#define __ACCOUNT_RECORD__

#include <string>
#include "date.h"
#include "account.h"
using namespace std;

class Account;
class AccountRecord{        //账目记录
    public:
        AccountRecord(Date &date,Account *account,double amount,double balance,string &desc);
        Date date;               //日期
        const Account *account;  //账户
        double amount;           //（操作的）金额
        double balance;          //余额
        string desc;             //描述存取款原因
};



#endif //__ACCOUNT_RECORD__
