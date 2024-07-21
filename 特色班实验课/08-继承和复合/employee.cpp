/*
某公司有经理（Manager）、销售（Sales）、销售经理（SalesManager）四类雇员（Employee），他们的薪酬计算方法各不一样：每个雇员（Employee）都有每月的基本工资；经理（Manager）除了基本工资之外还有每月分红；销售（Sales）除了基本工资之外，每月还有营销提成；销售经理（SalesManager）既是销售（Sales）人员也是经理（Manager），因此他既有每月的营销提成，也有每月分红。

其中，雇员（Employee）的月基本工资并不相同

销售（Sales）的提成是其销售额的百分之5.

经理(Manager)的每月分红是该部门的当月销售总额的千分之5.

下面请你根据以上描述，设计基类雇员（employee）,并由此派生出相关类，用于计算不同员工的工资。

输入：

一个正整数n,表示有几个员工，接下来的n行每行是相关员工的相关信息。分别表示其姓名，职务，月基本工资，销售额（作为销售才有），部门销售总额（作为经理才有）

输出：n行，代表每个员工的工资
*/
#include <iostream>
#include<string>
#include<cstdio>
#include<iomanip>
#include<vector>
#include<typeinfo>
using namespace std;
class Employee
{
public:
    string name;
    int basemoney;
    Employee(string n, int b) :name(n), basemoney(b) {}
    virtual void print() = 0;
};
class Employee1 :public Employee
{
public:
    Employee1(string n, int b) :Employee(n, b) {}
    void print() { cout  << basemoney  ; }
};
class Manager :public Employee
{
public:
    int k;
    Manager(string n, int b, int kk) :Employee(n, b), k(kk) {}
    void print() { cout << basemoney+k/200.0 ; }
};
class Sales :public Employee
{
public:
    int k;
    Sales(string n, int b, int kk) :Employee(n, b), k(kk) {}
    void print() { cout << basemoney+k/20.0 ; }
};
class SalesManager :public Employee
{
public:
    int k;
    int y;
    SalesManager(string n, int b, int kk, int yy) :Employee(n, b), k(kk), y(yy) {}
    void print() { cout << basemoney+k/20.0+y/200.0 ; }
};
int main()
{
    string label, name;
    Employee* p[100];
    int n;
    int base, royalty, bonus;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> name >> label;
        if (label == "Employee")
        {
            cin >> base;
            p[i] = new Employee1(name, base);
        }
        if (label == "Sales")
        {
            cin >> base >> royalty;
            p[i] = new Sales(name, base, royalty);
        }
        if (label == "Manager")
        {
            cin >> base >> bonus;
            p[i] = new Manager(name, base, bonus);
        }
        if (label == "SalesManager")
        {
            cin >> base >> royalty >> bonus;
            p[i] = new SalesManager(name, base, royalty, bonus);
        }
    }
    for (int i = 0; i < n; i++)
    {
        p[i]->print();
        // if (i != (n - 1))
        cout << endl;
    }
    for (int i = 0; i < n; i++)
        delete p[i];
}