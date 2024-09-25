/*
设计日期类Date和时间类Time，并以此两类为基类派生日期时间类DateTime，日期类包括年、月、日成员，时间类包括时、分、秒成员，日期时间类能够实现日期时间的求差、比较大小的功能。

 要求：

 1、重载==运算符，判断两个日期时间是否相等。

 2、重载<和>运算符，判断两个日期时间大小，规定：过去的时间比现在的时间小，比如2023-3-3 18:45:46 > 2022-7-8 19:54:56。

 3、重载减运算符-，可以对日期时间求差。

 4、假设每个月都是30天，不考虑闰年，不考虑公元前，24小时制，24点表示为0:0:0即可。

 5、输出格式为XX-XX-XX XX-XX-XX，日期和时间用空格隔开，内部用-隔开，如2019-1-8 18：12：0，其中秒不需要用“00”表示。

输入格式

 第 1 行：12个整数，分别是两个对象的 年、月、日、时、分、秒，空格隔开。

输出格式

 第 1 行：第一个对象的日期时间

 第 2 行：第二个对象的日期时间

 第 3 行：是否相等

 第 4 行：第一个对象是否大于第二个对象

 第 5 行：第一个对象是否小于第二个对象

 第 6 行：两个对象时间差，若dt1比dt2大，则输出dt1 - dt2，否则：dt2 - dt1
*/

#include<iostream>
using namespace std;
class Date
{
private:
	int year;
	int month;
	int day;
public:
	int getyear() { return year; }
	int getmonth() { return month; }
	int getday() { return day; }
	void setyear(int _year) { year = _year; }
	void setmonth(int _month) { month = _month; }
	void setday(int _day) { day = _day; }
	Date(int _year, int _month, int _day)
	{
		year = _year;
		month = _month;
		day = _day;
	}
};
class Time
{
private:
	int hour;
	int minute;
	int second;
public:
	int gethour() { return hour; }
	int getminute() { return minute; }
	int getsecond() { return second; }
	void sethour(int _hour) { hour = _hour; }
	void setminute(int _minute) { minute = _minute; }
	void setsecond(int _second) { second = _second; }
	Time(int _hour, int _minute, int _second)
	{
		hour = _hour;
		minute = _minute;
		second = _second;
	}
};
class DateTime : public Time, public Date
{
public:
	DateTime(int _year, int _month, int _day, int _hour, int _minute, int _second) :Time(_hour, _minute, _second), Date(_year, _month, _day) {};
	bool operator ==(DateTime& a)
	{
		if (getyear() != a.getyear())return false;
		else if (getmonth() != a.getmonth())return false;
		else if (getday() != a.getday())return false;
		else if (gethour() != a.gethour())return false;
		else if (getminute() != a.getminute())return false;
		else if (getsecond() != a.getsecond())return false;
		else return true;
	}
	bool operator >(DateTime& a)
	{
		if (getyear() > a.getyear())return true;
		else if (getyear() < a.getyear())return false;
		else if (getmonth() > a.getmonth())return true;
		else if (getmonth() < a.getmonth())return false;
		else if (getday() > a.getday())return true;
		else if (getday() < a.getday())return false;
		else if (gethour() > a.gethour())return true;
		else if (gethour() < a.gethour())return false;
		else if (getminute() > a.getminute())return true;
		else if (getminute() < a.getminute())return false;
		else if (getsecond() > a.getsecond())return true;
		else return false;
	}
	bool operator <(DateTime& a)
	{
		if (getyear() < a.getyear())return true;
		else if (getyear() > a.getyear())return false;
		else if (getmonth() < a.getmonth())return true;
		else if (getmonth() > a.getmonth())return false;
		else if (getday() < a.getday())return true;
		else if (getday() > a.getday())return false;
		else if (gethour() < a.gethour())return true;
		else if (gethour() > a.gethour())return false;
		else if (getminute() < a.getminute())return true;
		else if (getminute() > a.getminute())return false;
		else if (getsecond() < a.getsecond())return true;
		else return false;
	}
	DateTime operator -(DateTime& a)
	{
		DateTime ans(0, 0, 0, 0, 0, 0);
		int sec1, sec2;
		int final;
		sec1 = this->getyear() * 12 * 30 * 24 * 60 * 60 + this->getmonth() * 30 * 24 * 60 * 60 + this->getday() * 24 * 60 * 60 + this->gethour() * 60 * 60 + this->getminute() * 60 + this->getsecond();
		sec2 = a.getyear() * 12 * 30 * 24 * 60 * 60 + a.getmonth() * 30 * 24 * 60 * 60 + a.getday() * 24 * 60 * 60 + a.gethour() * 60 * 60 + a.getminute() * 60 + a.getsecond();
		if (sec1 >= sec2)
		{
			final = sec1 - sec2;
			ans.setsecond(final % 60);
			final -= ans.getsecond();
			ans.setminute(final % 3600/60);
			final -= ans.getminute() * 60;
			ans.sethour(final % (3600 * 24)/(3600));
			final -= ans.gethour() * 3600;
			ans.setday(final % (3600 * 24 * 30)/(24*3600));
			final -= ans.getday() * 24 * 3600;
			ans.setmonth(final % (12 * 30 * 24 * 3600)/(30*24*3600));
			final -= ans.getmonth() * 30 * 24 * 3600;
			ans.setyear(final / (12 * 30 * 24 * 3600));
		}
		else
		{
			final = sec2 - sec1;
			ans.setsecond(final % 60);
			final -= ans.getsecond();
			ans.setminute(final % 3600 / 60);
			final -= ans.getminute() * 60;
			ans.sethour(final % (3600 * 24) / (3600));
			final -= ans.gethour() * 3600;
			ans.setday(final % (3600 * 24 * 30) / (24 * 3600));
			final -= ans.getday() * 24 * 3600;
			ans.setmonth(final % (12 * 30 * 24 * 3600) / (30 * 24 * 3600));
			final -= ans.getmonth() * 30 * 24 * 3600;
			ans.setyear(final / (12 * 30 * 24 * 3600));
		}
		return ans;
	}

};
int main()
{
	int year1, month1, day1, hour1, minute1, second1;
	int year2, month2, day2, hour2, minute2, second2;
	cin >> year1 >> month1 >> day1 >> hour1 >> minute1 >> second1 >> year2 >> month2 >> day2 >> hour2 >> minute2 >> second2;
	DateTime a1(year1, month1, day1, hour1, minute1, second1);
	DateTime a2(year2, month2, day2, hour2, minute2, second2);
	cout << a1.getyear() << "-" << a1.getmonth() << "-" << a1.getday() << " " << a1.gethour() << ":" << a1.getminute() << ":" << a1.getsecond() << endl;
	cout << a2.getyear() << "-" << a2.getmonth() << "-" << a2.getday() << " " << a2.gethour() << ":" << a2.getminute() << ":" << a2.getsecond() << endl;
	if (a1 == a2)cout << "dt1 == dt2 : true" << endl;
	else cout << "dt1 == dt2 : false" << endl;
	if (a1 > a2)cout << "dt1 > dt2 : true" << endl;
	else cout << "dt1 > dt2 : false" << endl;
	if (a1 < a2)cout << "dt1 < dt2 : true" << endl;
	else cout << "dt1 < dt2 : false" << endl;
	
	if (a1 > a2) 
    {   DateTime b = a1 - a2;
        cout << "dt1 - dt2 : " << b.getyear() << "-" << b.getmonth() << "-" << b.getday() << " " << b.gethour() << ":" << b.getminute() << ":" << b.getsecond();}
	else {
        DateTime b = a2 - a1;
        cout << "dt2 - dt1 : " << b.getyear() << "-" << b.getmonth() << "-" << b.getday() << " " << b.gethour() << ":" << b.getminute() << ":" << b.getsecond();}
    cout<<endl;
}