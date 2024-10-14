#include<iostream>
using namespace std;
int main()
{
	char input,change;
	int changeint, intchange;
	cin >> input >> change>> intchange;
	changeint = input;
	cout << changeint<<endl ;
	cout << change - input<<endl;
	cout << (char)intchange;
	return 0;
}