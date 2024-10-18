#include<iostream>
#include<string>
#include<cmath>
using namespace std;
class student
{
public:
	int chinese;
	int maths;
	int English;
	int sum;
	string name;
	student()
	{
		cin>> name >> chinese >> maths >> English ;
		sum = chinese + maths + English;
	}
	bool operator==(student& stu) const
	{
		if (fabs(chinese - stu.chinese) <= 5 && fabs(maths - stu.maths) <= 5 && fabs(English - stu.English) <= 5 && fabs(sum - stu.sum) <= 10) return true;
		return false;
	}
};
int main()
{
	int n;
	cin >> n;
	student* p = new student[n];
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
			if (p[i] == p[j])
				cout << p[i].name << " " << p[j].name << endl;
	}
	delete []p;
	return 0;
}
