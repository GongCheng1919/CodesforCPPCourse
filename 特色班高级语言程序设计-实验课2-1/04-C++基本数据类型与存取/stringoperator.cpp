#include<iostream>
#include<string>
using namespace std;
int main()
{
	string str1,str2;
	getline(cin, str1);
	getline(cin, str2);
	int start, end,m;
	cin >> start >> end>>m;
	string str3= str1 + str2;
	cout << str3<<endl;
	for (auto i = str1.begin(); i != str1.end(); i++)
	{
		*i = toupper(*i);
	}
	for (auto i = str2.begin(); i != str2.end(); i++)
	{
		*i = tolower(*i);
	}
	cout << str1 << endl << str2 << endl;
	str1 > str2 ? cout << "yes" : cout << "no";
	string s2 = str3.substr(start,end);
	cout << endl << s2<<endl;
	string output;
	int size = str3.size();
	int d = 0,num=0;
	for (int i = 0; ; i++)
	{
		if (str3[i] != 0) d++;
		if (d == m) {
			d = 0; output += str3[i];  str3[i] = 0;num++;
		}
		if (num == size) break;
		if (i == size - 1) i = -1;
	}
	cout << output;
	return 0;
}
