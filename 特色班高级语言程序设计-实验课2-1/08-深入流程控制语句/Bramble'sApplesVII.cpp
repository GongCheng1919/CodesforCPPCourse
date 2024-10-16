#include<iostream>
using namespace std;
int main()
{
	int n,m;
	cin >> n>>m;
	if (n <= 0||m<=0) {
		cout << "error"; return 0;
	}
	int* p,*p1;
	p = new int[n];
	p1 = new int[n];
	for (int i = 0; i < n; i++)
	{
		p[i] = i + 1;
	}
	int d = 0,num=0;
	for (int i = 0; ; i++)
	{
		if (p[i] != 0) d++;
		if (d == m) {
			d = 0; p1[num] = p[i]; num++; p[i] = 0;
		}
		if (num == n ) break;
		if (i == n - 1) i = -1;
	}
	delete p;
	for (int i = 0; i < n; i++)
	{
		cout << p1[i];
		if (i != n - 1) cout << "->";
	}
	return 0;
}
