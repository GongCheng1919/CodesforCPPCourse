#include<iostream>
using namespace std;
union type{
	double d;
	float f[2];
	int i[2];
	long l;
	char c[8];
};
int main()
{
	type ty;
	cin >> ty.d;
	cout << ty.i[0] <<" "<< ty.i[1] << endl;
	cout << ty.f[0] <<" "<< ty.f[1] << endl;
	for (int i = 0; i < 8; i++)
	{
		cout << ty.c[i];
		if (i != 7)cout << " ";
	}
	cout << endl;
	cout << ty.l;
	return 0;
}
