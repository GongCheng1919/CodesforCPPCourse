#include<iostream>
#include<cmath>
#include<string>
using namespace std;
class INT
{
public:
	int* data;
	int size;
	int fuhao;
	INT(int x)
	{
		data = new int[4000];
		for (int i = 0; i < 4000; i++)
			data[i] = 0;
		if (x == 0) {
			size = 1; fuhao = 1; return;
		}
		fuhao = x / fabs(x);
		x = fabs(x);
		size = 0;
		while (x != 0)
		{
			data[size++] = x % 10;
			x /= 10;
		}
	}
	INT()
	{
		data = new int[4000] ;
		for (int i = 0; i < 4000; i++)
			data[i] = 0;
		size = 1;
		fuhao = 1;
	}
	~INT()
	{
		delete[]data;
	}
	INT(const INT& in)
	{
		data = new int[4000];
		for (int i = 0; i < 4000; i++)
			data[i] = 0;
		size = in.size;
		for (int i = 0; i < size; i++)
			data[i] = in.data[i];
		fuhao = in.fuhao;
	}
	INT(string str)
	{
		data = new int[4000] ;
		for (int i = 0; i < 4000; i++)
			data[i] = 0;
		size = str.size();
		fuhao = 1;
		int i = 0;
		for (int j = size - 1; j >= 0; j--)
		{
			if (str[j] != '-')
			{
				data[i++] = str[j] - '0';
			}
		}
		if (str[0] == '-') { fuhao = -1; size--; }
	}
	void operator=(const INT& in)
	{
		delete data;
		data = new int[4000] ;
		for (int i = 0; i < 4000; i++)
			data[i] = 0;
		size = in.size;
		for (int i = 0; i < size; i++)
		{
			data[i] = in.data[i];
		}
		fuhao = in.fuhao;
	}
	void clear()
	{
		delete data;
		size = 0;
		fuhao = 1;
		data = new int[4000] ;
		for (int i = 0; i < 4000; i++)
			data[i] = 0;
	}
};
ostream& operator<<(ostream& os,INT& in)
{
	if (in.fuhao < 0) cout << "-";
	for (int i = in.size - 1; i >= 0; i--)
	{
		os << in.data[i];
	}
	return os;
}

INT operator+(INT in1,INT in2) 
{
	INT output;
	if (in1.fuhao == in2.fuhao) {
		output.fuhao = in1.fuhao;
		output.size = max(in1.size, in2.size);
		for (int i = 0; i < output.size; i++)
		{
			output.data[i] = in1.data[i] + in2.data[i];
		}
		for (int i = 0; i < output.size; i++)
		{
			if (i == output.size - 1)
			{
				if (output.data[i] >= 10) 
				{
					output.data[i] -= 10;
					output.data[output.size++] = 1;
				}
			}
			else
			{
				if (output.data[i] >= 10)
				{
					output.data[i] -= 10;
					output.data[i + 1]++;
				}
			}
		}
		cout << "INT and INT has been called"<<endl;
		return output;
	}
	else
	{
		output.size = max(in1.size, in2.size);
		for (int i = 0; i < output.size; i++)
		{
			output.data[i] = in1.data[i] - in2.data[i];
		}
		for (int i = 0; i < output.size; i++)
		{
			if (i != output.size - 1)
			{
				if (output.data[i] < 0) {
					output.data[i] += 10;
					output.data[i + 1]--;
				}
			}
			else if (output.data[i] == 0) {
				output.size--;
			}
		}
		output.fuhao = output.data[output.size - 1] * in1.fuhao / fabs(output.data[output.size - 1]);
		for (int i = 0; i < output.size; i++)
		{
			output.data[i] = fabs(output.data[i]);
		}
		return output;
	}
	
}
INT operator+(INT in1, int in2)
{
	cout << "INT and int has been called" << endl;
	INT output;
	output = in1 + INT(in2);
	return output;
}
INT operator*(INT& in1, INT& in2)
{
	INT output, temp;
	output.fuhao = in1.fuhao * in2.fuhao;
	for (int i = 0; i < in1.size; i++)
	{
		if (in1.data[i] == 0)continue;
		temp.size = i + in2.size;
		temp.fuhao = output.fuhao;
		for (int j = 0; j < in2.size; j++)
		{
			temp.data[i + j] = in2.data[j] * in1.data[i];
		}
		for (int j = i; j < temp.size; j++)
		{
			if (j != temp.size - 1)
			{
				if (temp.data[j] >= 10)
				{
					temp.data[j + 1] += temp.data[j] / 10;
					temp.data[j] %= 10;
				}
			}
			else if (temp.data[j] >= 10)
			{
				temp.data[temp.size++] = temp.data[j] / 10;
				temp.data[j] %= 10;
			}
		}
		output = output + temp;
		temp.clear();
	}
	return output;
}
int main()
{
	string str;
	cin >> str;
	INT i1(str);
	int x;
	cin >> x;
	INT i3;
	i3 = i1 + x;
	i3 = i1 + INT(x);
	cout << i3;
	return 0;
}
