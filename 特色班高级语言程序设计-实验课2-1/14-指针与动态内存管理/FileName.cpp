#include<iostream>
#include<fstream>
using namespace std;
fstream out("test.txt", ios::out);
template<typename T>
class stack
{
private:
	T* data;//��ջ�����ݵ�
	int capacity;//����
	int size;//Ŀǰ�ж���Ԫ��
	int Expansion = 2;//����ϵ��
public:
	stack()//��ʼ��ջ�������20��Ԫ�ص�λ��
	{
		capacity = 2;
		data = new T[2];
		size = 0;
	}
	void pushback(T x);//��ջ
	T pop()//��ջ
	{
		return data[--size];
	}
	bool empty()//�ж�ջ�Ƿ�Ϊ��
	{
		if (size == 0)return true;
		return false;
	}
	T inquire()//��ѯջ��Ԫ��
	{
		return data[size - 1];
	}
	int getsize()//��ȡջ�ĳ���
	{
		return size;
	}
	void clear()//���ջ
	{
		delete[]data;
		data = new T[20];
		size = 0;
		capacity = 20;
	}
	~stack()//����
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
	if (size + 1 < capacity) data[size++] = x;//����ջһ��Ԫ�غ��sizeС��������ֱ����ջ
	else//�����ڣ����ݺ�ԭ���ݿ������¿ռ䲢�ͷ�ԭ�ռ�
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
		out << "Increase capacity to " << capacity << endl;
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
	out << sta;
	return 0;
}