#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;
class school
{
public:
	char career;
	enum sex{male,female} s;
	union scoreandsalary
	{
		struct score
		{
			int chinese;
			int maths;
			int English;
		} sc;
		struct salary
		{
			int gongzi;
			int nianzhongjiang;
		} sa;
	}sas;
	int sum;
	string name;
	school()
	{
		cin >> career;
		int sex;
		cin >> sex;
		if (sex == 0) s = male;
		else s = female;
		cin >> name;
		if (career == 's')
		{
			cin >> sas.sc.chinese >> sas.sc.maths >> sas.sc.English;
			sum = sas.sc.chinese + sas.sc.maths + sas.sc.English;
		}
		else
		{
			cin >> sas.sa.gongzi >> sas.sa.nianzhongjiang;
			sum = sas.sa.gongzi * 12 + sas.sa.nianzhongjiang;
		}
	}
	bool operator<(school& sc)
	{
		if (sum > sc.sum) return true;
		return false;
	}
};
ostream& operator<<(ostream& os, school& sc)
{
	os << sc.name<<" ";
	if (sc.s) cout << "female";
	else cout << "male";
	cout << " ";
	if (sc.career == 's') { os << sc.sas.sc.chinese << " " << sc.sas.sc.maths << " " << sc.sas.sc.English; }
	else { os << sc.sas.sa.gongzi << " " << sc.sas.sa.nianzhongjiang; }
	return os;
}
school& search(vector<school>& sc)
{
	int max=-1;
	for (school s : sc)
		if (max < s.sum) max = s.sum;
	if (max == sc.front().sum) return sc.front();
	else sort(sc.begin(), sc.end());
	return sc.front();
}
int main()
{
	int n;
	cin >> n;
	vector<school> student;
	vector<school> teacher;
	school* p = new school [n] ;
	for (int i = 0; i < n; i++)
	{
		if (p[i].career == 's') student.push_back(p[i]);
		else teacher.push_back(p[i]);
	}
	cout << search(student)<<endl << search(teacher);
	delete[]p;
	return 0;
}
