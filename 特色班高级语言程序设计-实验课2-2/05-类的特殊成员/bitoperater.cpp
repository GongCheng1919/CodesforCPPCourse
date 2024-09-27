#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
int main()
{
	int bitop(int num1, int num2, char op, int start_bit, int end_bit);
	int num1, num2, start_bit, end_bit,output;
	char op;
	cin >> num1 >> num2 >> op >> start_bit >> end_bit;
	output=bitop(num1, num2, op, start_bit, end_bit);
	if (output != -1)
		cout << output;
	else
		cout << "error";
	return 0;
}
int bitop(int num1, int num2, char op, int start_bit, int end_bit)
{
	int i, num[32], d = 0, num3[32],output=0;
	vector<int>v;
	for (i = 31; i >= 0; i--, d++)
	{
		num[d] = ((num1 >> i) & 1);
		num3[d] = ((num2 >> i) & 1);
		v.push_back(num[d]);
	}
	switch (op)
	{
	case'&':
		if (start_bit > end_bit || end_bit > 32) return -1;
		for (i = 0; i < 32; i++)
		{
			if (i >= start_bit && i <= end_bit)
			{
				if (num[31-i] == 1 && num3[31-i] == 1) v[31-i] = 1;
				else v[31-i] = 0;
			}
			else v[31-i] = 0;
		}
		for (i = 31,d=0; i >= 0; i--,d++)
		{
			output += pow(2, d) * v[i];
		}
		return output;
	case'|':
		if (start_bit > end_bit || end_bit > 32) return -1;
		for (i = 0; i < 32; i++)
		{
			if (i >= start_bit && i <= end_bit)
			{
				if (num[31 - i] == 0 && num3[31 - i] == 0) v[31 - i] = 0;
				else v[31 - i] = 1;
			}
			else v[31 - i] =0;
		}
		for (i = 31, d = 0; i >= 0; i--, d++)
		{
			output += pow(2, d) * v[i];
		}
		return output;
	case'^':
		if (start_bit > end_bit || end_bit > 32) return -1;
		for (i = 0; i < 32; i++)
		{
			if (i >= start_bit && i <= end_bit)
			{
				if (num[31 - i] ==  num3[31 - i]) v[31 - i] = 0;
				else v[31 - i] = 1;
			}
			else v[31 - i] = 0;
		}
		for (i = 31, d = 0; i >= 0; i--, d++)
		{
			output += pow(2, d) * v[i];
		}
		return output;
	case'~':
		if (start_bit > end_bit || end_bit > 32) return -1;
		for (i = 0; i < 32; i++)
		{
			if (i >= start_bit && i <= end_bit)
			{
				if (num[31 - i] == 1) v[31 - i] = 0;
				else v[31 - i] = 1;
			}
			else v[31 - i] = 0
				;
		}
		for (i = 31, d = 0; i >= 0; i--, d++)
		{
			output += pow(2, d) * v[i];
		}
		return output;
	case'>':
		if (start_bit > end_bit || end_bit > 32) return -1;
		for (i = 0; i < 32; i++)
		{
			v[31 - i] = 0;
		}
		for (i = start_bit; i <= end_bit; i++)
			v[31 - i] = num[31 - i];
		for (i = 0; i < num2; i++)
		{
			v.erase(v.end()-start_bit-1, v.end() - start_bit);
			v.insert(v.begin() , 0);
		}
		for (i = 31, d = 0; i >= 0; i--, d++)
		{
			output += pow(2, d) * v[i];
		}
		return output;
	case'<':
		for (i = 0; i < 32; i++)
		{
			v[31 - i] = 0;
		}
		for (i = start_bit; i <= end_bit; i++)
			v[31 - i] = num[31 - i];
		for (i = 0; i < num2; i++)
		{
			v.insert(v.begin()+end_bit, 0);
			v.erase(v.begin()+end_bit,v.begin()+end_bit+1);
		}
		for (i = 31, d = 0; i >= 0; i--, d++)
		{
			output += pow(2, d) * v[i];
		}
		return output;
	}
}