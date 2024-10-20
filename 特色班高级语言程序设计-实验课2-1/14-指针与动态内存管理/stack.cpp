#include<iostream>
using namespace std;
template<typename T>
class stack
{
private:
	T* data;//存栈内数据的
	int capacity;//容量
	int size;//目前有多少元素
	int Expansion = 2;//扩容系数
public:
	stack()//初始化栈，最初有20个元素的位置
	{
		capacity = 2;
		data = new T[2];
		size = 0;
	}
	void pushback(T x);//入栈
	T pop()//出栈
	{
		return data[--size];
	}
	bool empty()//判断栈是否为空
	{
		if (size == 0)return true;
		return false;
	}
	T inquire()//查询栈顶元素
	{
		return data[size - 1];
	}
	int getsize()//获取栈的长度
	{
		return size;
	}
	void clear()//清空栈
	{
		delete[]data;
		data = new T[20];
		size = 0;
		capacity = 20;
	}
	~stack()//析构
	{
		delete[]data;
	}
	friend std::ostream& operator<<(std::ostream& os, const stack<T>& sta)
	{
		for (int i = 0; i < sta.size; i++)
		{
			os << sta.data[i] << " ";
		}
		return os;
	};
};
template<typename T>
void stack<T>::pushback(T x)
{
	if (size + 1 < capacity) data[size++] = x;//若入栈一个元素后的size小于容量，直接入栈
	else//若大于，扩容后将原数据拷贝到新空间并释放原空间
	{
		capacity *= Expansion;
		T* temp = new T[capacity];
		for (int i = 0; i < size; i++)
		{
			temp[i] = data[i];
		}
		temp[size++] = x;
		delete[]data;
		data = temp;
		cout << "Increase capacity to " << capacity << endl;
	}
}
int main()
{

	int n;
	cin >> n;
	stack<int> sta;
	for (int i = 0; i < n; i++)
	{
		int temp;
		char c;
		cin >> temp >> c;
		if (c == 'i') sta.pushback(temp);
		else sta.pop();
	}
	cout << sta;
	return 0;
}
