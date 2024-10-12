#include<iostream>
#include<iomanip>
using namespace std;
int main()
{
	double origin,change2;
	int change1;
	float change3;
	cin >> origin;
	change1 = static_cast<int>(origin);
	change2 = static_cast<double>(change1);
	change3 = static_cast<float>(origin);
	cout << std::setprecision(40) << std::fixed << origin << endl << change1 << endl << change2 << endl << change3;
	return 0;
}
