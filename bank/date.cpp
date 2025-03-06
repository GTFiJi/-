//date.cpp
#include "date.h"
#include <bits/stdc++.h>
using namespace std;

//日期构造或者输入错误
Date::Date(int year,int month,int day):year(year),month(month),day(day){
    if (  day<=0 || day > getMaxDay()
        || month<=0 || month>12)
    {
		throw DateException();
    }
};

string Date::show() const{
    return to_string(year)+'-'+to_string(month)+'-'+ to_string(day);
};
//Date类型的数据都做为键，后面这些operator重置运算符都用于直接加减与比较Date
bool Date::operator < (const Date& d) const
{
	if (year < d.year)
	{
		return true;
	}
	else if (year == d.year)
	{
		if (month < d.month)
			return true;
		else if ((month == d.month) && (day < d.day))
			return true;
		else
			return false;
	}
	else
		return false;
}
//比较两个日期对象是否相等
bool Date::operator==(const Date& d)
{
	if ((year == d.year) && (month == d.month) && (day == d.day))
		return true;
	else
		return false;
}
//比较当前日期是否晚于或等于另一个日期对象
bool Date::operator>=(const Date& d)
{
	return (*this > d || *this == d);
}
//比较两个日期对象是否不相等
bool Date::operator!=(const Date& d)
{
	return !(*this == d);
}
//比较当前日期是否早于或等于另一个日期对象
bool Date::operator<=(const Date& d)
{
    return *this == d || *this < d;
}
//比较当前日期是否晚于另一个日期对象
bool Date::operator>(const Date& d)
{
    return !(*this <= d);
}
//将当前日期加上指定的天数，并返回当前日期对象的引用
Date& Date::operator+=(int days)
{
    day += days;//先加
	//这里是while,因为如果是if的话，如果一次加了很大的数据减一次不一定能减得完!!!
	while(day > getMaxDay())
	{
		day -= getMaxDay();
		++month;
		if (month == 13)
		{
			++year;
			month = 1;
		}
	}
	return *this;
}
//返回一个新的日期对象，该对象的日期为当前日期加上指定的天数
Date Date::operator+(int day)
{
	Date tmp=*this;

   
	tmp += day;
	return tmp;
}

//Date& operator-=(int day)
Date& Date::operator-=(int days)
{
    day -= days;
	while (day <= 0)
	{
		--month;
		if (month == 0)
		{
			--year;
			month = 12;
		}
		day += getMaxDay();
	}
	return *this;
}

//返回一个新的日期对象，该对象的日期为当前日期减去指定的天数
Date Date::operator-(int day)
{
	Date tmp = *this;
	tmp -= day;
	return tmp;
}
//前置自增运算符，将当前日期增加一天，并返回当前日期对象的引用
Date& Date::operator++()
{
	return *this += 1;
}
//后置自增运算符，返回增加一天前的日期对象，并将当前日期增加一天
Date Date::operator++(int) 
{
	Date tmp = *this;
	
	*this += 1;
	return tmp;
}
//前置自减运算符，将当前日期减去一天，并返回当前日期对象的引用
Date& Date::operator--()
{
	*this - 1;
	return *this;
}
//后置自减运算符，返回减少一天前的日期对象，并将当前日期减去一天
Date Date::operator--(int)
{
	Date tmp = *this;
	*this -= 1;
	return tmp;
}
//返回两个日期对象之间的天数差
int Date::operator-(const Date& d)
{
	int flag = 1;
	Date max = *this;
	Date min = d;

	if (*this < d)
	{
		//赋值为-1的原因：因为这个函数是有顺序的d1-d2，如果遇到d1<d2，也就是小减大，最终返回的结果是个负数，所以说这里要变成-1。
		flag = -1;
		max = d;
		min = *this;
	}
	//定义一个变量
	int n = 0;
	// 用循环算两个日期中间的差值

	while (min != max)
	{
		++min;
		++n;
	}
	return n * flag;
}
