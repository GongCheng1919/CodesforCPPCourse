#include<iostream>
#include<string>
using namespace std;
int main()
{
	string name;
	int age;
	double chinese, maths, English,ave;
	bool extraclass;
	cin >> name >> age >> chinese >> maths >> English >> extraclass;
	ave = (chinese + maths + English) / 3;
	if (extraclass) ave += 5;
	if (ave > 100)ave = 100;
	cout << "Name:" << name<<endl;
	cout << "age:" << age << endl;
	cout << "Chinese:" << chinese << endl;
	cout << "maths:" << maths << endl;
	cout << "English:" << English << endl;
	cout << "ave:" << ave << endl;
	if (ave > 60) cout << "ifpass:pass" ;
	else cout << "ifpass:fail";
	if (extraclass) cout <<endl<< "参加额外课程，已加五分";
	return 0;
}
