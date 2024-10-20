#include<iostream>
#include<string>
using namespace std;
class link//ջ�ĵ�λ
{
public:
	link* next;//ÿ����λ��¼��һ����λ�ĵ�ַ
	string data;//ÿ����λ��Ӧһ����
	string key;
	link(string d, string k) :data(d), key(k) { next = nullptr; };
};
class stack//ջ��
{
public:
	link* head;//ָ��ջ�ڵ�һ����λ��ָ��
	link* curr;//βָ��
	void newlink(string key, string data);//�����µ�λ�ĺ���
	void deletelink(link* lin);//ɾ��ĳ����λ�ĺ���
	stack()//�����µ�ջ���캯��
	{
		head = nullptr;//��ͷָ������Ϊ��
		curr = head;
	}
	~stack()//����
	{
		link* temp = head;
		while (temp != curr)//��ͷָ�벻Ϊ��ָ��ʱ����
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