#include<iostream>
using namespace std;
int main()
{
	double d;
	cin >> d;
	double* p = &d;
	int* p1 = (int*)p;
	cout << p1[0] << " " << p1[1]<<endl;
	float* f=(float*) p;
	cout << f[0] << " " << f[1] << endl;
	char* c = (char*)p;
	for (int i = 0; i < 8; i++)
	{
		cout << c[i];
		if (i != 7)cout << " ";
	}
	cout << endl;
	long* l = (long*)p;
	cout << l[0];
	return 0;
}
