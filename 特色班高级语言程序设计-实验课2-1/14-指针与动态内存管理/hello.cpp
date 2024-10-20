#include<iostream>
#include<string>
using namespace std;
class link//栈的单位
{
public:
	link* next;//每个单位记录下一个单位的地址
	string data;//每个单位对应一个块
	string key;
	link(string d, string k) :data(d), key(k) { next = nullptr; };
};
class stack//栈类
{
public:
	link* head;//指向栈内第一个单位的指针
	link* curr;//尾指针
	void newlink(string key, string data);//创建新单位的函数
	void deletelink(link* lin);//删除某个单位的函数
	stack()//创建新的栈构造函数
	{
		head = nullptr;//将头指针设置为空
		curr = head;
	}
	~stack()//析构
	{
		link* temp = head;
		while (temp != curr)//当头指针不为空指针时进行
		{
			link* te;
			if (temp == nullptr)break;
			te = temp->next;
			cout << temp->key << " " << temp->data << endl;
			delete temp;
			temp = nullptr;
			temp = te;

		}
		cout << curr->key << " " << curr->data;
		delete curr;
	}
};
ostream& operator<<(ostream& os, stack& st)
{
	link* now = st.head;
	while (now != nullptr)
	{
		os << now->key << " " << now->data;
		if (now->next != nullptr) os << endl;
		now = now->next;
		if (now == nullptr)break;
	}
	return os;
}
void stack::newlink(string key, string data)
{
	link* temp;
	temp = new link(data, key);
	if (curr != nullptr) {
		curr->next = temp;
		curr = temp;
	}
	else { head = temp; curr = temp; }
}
void stack::deletelink(link* lin)
{
	link* temp = head;
	if (head == lin) { head = lin->next; delete lin; lin = nullptr; return; }
	while (temp->next != lin&&temp!=nullptr)
	{
		temp = temp->next;
		if (temp->next == lin) break;
		
	}
	temp->next = lin->next;
	if (lin == curr) curr = temp;
	delete lin;
	lin = nullptr;
}
stack sta;
void insert(string key, string data)
{
	sta.newlink(key, data);
}
void delet(string key, string data)
{
	link* now = sta.head;
	while (now != nullptr)
	{
		if (now->key == key) break;
		now = now->next;
	}
	if (now != nullptr) sta.deletelink(now);
}
void update(string key, string value)
{
	link* now = sta.head;
	while (now != nullptr)
	{
		if (now->key == key) { now->data = value; break; }
		now = now->next;
	}
}
int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		char c;
		string key1, value1;
		cin >> key1 >> value1 >> c;
		switch (c)
		{
		case'i':insert(key1, value1); break;
		case'd':delet(key1, value1); break;
		case'u':update(key1, value1); break;
		case'q':break;
		default:cout << "error" << endl; break;
		}
	}
	//cout << sta;
	return 0;
}