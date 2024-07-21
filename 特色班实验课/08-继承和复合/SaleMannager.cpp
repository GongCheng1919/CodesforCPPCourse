#include<iostream>
#include<string>
using namespace std;
class Employee {
	int wages;
public:
	Employee(int num):wages(num){}
	int get_wage() {
		return wages;
	}
};
class Sales :public Employee {
	int sale;
public:
	Sales(int num1,int num2):Employee(num1),sale(num2){}
	int get_wage() {
		return Employee::get_wage() + 0.05 * sale;
	}
};
class Manager :public Employee {
	int sum_sale;
public:
	Manager(int num1,int num2):Employee(num1),sum_sale(num2){}
	int get_wage() {
		return Employee::get_wage() + 0.005 * sum_sale;
	}
};
class Sale_Manager :public Sales, public Manager {
public:
	Sale_Manager(int num1, int num2, int num3) :Sales(num1, num2), Manager(num1, num3) {}
	int get_wage() {
		return Sales::get_wage() + Manager::get_wage() - Sales::Employee::get_wage();
	}
};
int main() {
	int n;
	cin >> n;
	int arr[100];
	for (int i = 0;i < n;i++) {
		string str1, str2;
		cin >> str1 >> str2;
		if (str2 == "Employee")
		{
			int wage;
			cin >> wage;
			Employee e(wage);
			arr[i] = e.Employee::get_wage();
		}
		else if (str2 == "Sales")
		{
			int wage, sale;
			cin >> wage >> sale;
			Sales s(wage, sale);
			arr[i] = s.Sales::get_wage();
		}
		else if (str2 == "Manager")
		{
			int wage, sum_sale;
			cin >> wage >> sum_sale;
			Manager m(wage, sum_sale);
			arr[i] = m.Manager::get_wage();
		}
		else if (str2 == "SalesManager")
		{
			int wage, sale, sum_sale;
			cin >> wage >> sale >> sum_sale;
			Sale_Manager sm(wage, sale, sum_sale);
			arr[i] = sm.get_wage();
		}
	}
	for (int i = 0;i < n;i++)
		cout << arr[i] << endl;
}