#include<iostream>
#include<cmath>
using namespace std;
int main()
{
	int max,sum=0,sunnum=0;
	cin >> max;
	int i = 2;
	if (max == 1 || max == 0) {
		cout << "0"; return 0;
	}
	do
	{
		int ifsushu = 1;
		if (i == 2) { sum += i; sunnum++; cout << i << endl; continue; }
		for (int j = 2; j <= sqrt(i); j++)
		{
			if (i % j == 0) {
				ifsushu = 0; break;
			}
		}
		if (ifsushu) {
			
			if (sum + i <= max) { sum += i; sunnum++; cout << i << endl; }
			else break;
		}

	} while (i++);
	cout << sunnum;
	return 0;
}
