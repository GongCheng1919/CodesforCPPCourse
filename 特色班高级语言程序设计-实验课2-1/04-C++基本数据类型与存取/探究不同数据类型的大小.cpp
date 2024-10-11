#include<iostream>
#include<string>
using namespace std;
int main()
{
	char c;
	cin >> c;
	switch (c)
	{
	case'c':cout << sizeof(char); break;
	case'i':cout << sizeof(int); break;
	case'd':cout << sizeof(double); break;
	case'f':cout << sizeof(float); break;
	case'l':cout << sizeof(long); break;
	case's':cout << sizeof(string); break;
	case'*':cout << sizeof(int*) << " " << sizeof(char*) << " " << sizeof(double*) << " " << sizeof(float*) << " " << sizeof(long*) << " " << sizeof(string*)<<" "<<sizeof(bool*); break;
	case'b':cout << sizeof(bool); break;
	default:cout << "error"; break;
	}
	return 0;
}
