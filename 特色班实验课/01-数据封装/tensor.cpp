#include<iostream>
#include<stdlib.h>

struct Tensor
{
	int dim_num; 	//dimension
	int size;

	int* dim_value;  //the size of dimensions
	int* data;
};

Tensor CreateTensor(int dim_num, int* dim_value, int(*p)(Tensor t));
int GetSize(Tensor t);
int GetElement(int* dim_index, Tensor t);
void Display(Tensor t);

using namespace std;

int main()
{
	int dim_num;
	cin >> dim_num;
	int* dim_value = new int[100000];

	int* dim_index = new int[100000];  //separate from Tensor

	for (int i = 0; i < dim_num; i++)
	{
		cin >> dim_value[i];
		if (dim_value[i] <= 0)
		{
			exit(1);
		}
	}
	for (int i = 0; i < dim_num; i++)
	{
		cin >> dim_index[i];
		if (dim_index[i] < 0)
		{
			exit(1);
		}
	}
	Tensor t=CreateTensor(dim_num, dim_value,GetSize);
	cout << GetSize(t) << endl << GetElement(dim_index, t) << endl;
	Display(t);

	return 0;
}

Tensor CreateTensor(int dim_num, int* dim_value,int(*p)(Tensor t))
{
	Tensor tensor;
	tensor.dim_num = dim_num;
	tensor.dim_value = dim_value;
	tensor.size = p(tensor);

	tensor.data = new int[100000];
	for (int i = 0; i < tensor.size; i++)
		tensor.data[i] = i + 1;
	return tensor;
}

int GetSize(Tensor t)
{
	int size = 1;
	for (int i = 0; i < t.dim_num; i++)
		size *= t.dim_value[i]; //
	return size;
}

int GetElement(int* dim_index, Tensor t)
{
	int dim_i = 0;
	for (int i = 0; i < t.dim_num-1; i++)
	{
		int sum = 1;
		for (int j=0;j<t.dim_num-1-i;j++)
		{
			sum *= t.dim_value[j];
		}
		dim_i += dim_index[i] * sum;
	}
	dim_i += dim_index[t.dim_num - 1];
	return t.data[dim_i];
}

void Display(Tensor t)
{
	for (int i = 1, j = 0; j < t.size; i++, j++)
	{
		cout << t.data[j];
		if (i%t.dim_value[t.dim_num-1] == 0)
		{
			i = 0;
			cout << '\n';
		}
		else
			cout << " ";
	}
}