#include<iostream>
using namespace std;
int main()
{
	int n;
	cin>>n;
	int* p = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> p[i];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = i+1; j < n; j++)
		{
			if (p[i] > p[j])
			{
				int temp = p[i];
				p[i] = p[j];
				p[j] = temp;
			}
			if (p[i] == p[j])
			{
				p[j] = 0;
			}
		}
	}
	int num = 0;
	for (int i = 0; i < n; i++)
	{
		if (p[i] != 0) 
		{
			num++;
		}
	}
	cout << num << endl;
	for (int i = 0; i < n; i++)
	{
		if (p[i] != 0)
		{
			cout << p[i];
			if (i != n - 1) cout << " ";
		}
	}
	return 0;
}
