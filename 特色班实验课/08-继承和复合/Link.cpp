/*
设计一个线性表类，再根据该线性表类分别派生出队列类（先进先出）和栈类（先进后出）在主函数中进行测试。

对于线性表类的设计，你应该先设计一个节点类（data），然后再利用类的组合，设计一个线性表类，该类应该保存头节点和尾节点，便于从头部插入和从尾部插入。

对于派生出来的队列类和栈类，你应该实现的成员函数有

void pop()，在栈中弹出栈顶元素,在队列中弹出队首元素

void insert(data t),在栈中实现元素的压栈，在队列中实现元素的入队

void print(),用于将栈和队列的元素给打印出来，按照对应的pop顺序打印

你将在主函数中根据要求实现一个栈的构造和一个队列的构造，然后再对其进行相关的操作，最后打印出栈和队列中的元素

输入

一个整数n，代表初始栈和队列的元素个数

一行n个整数，用于构造初始的栈和队列

一个整数m，代表接下来的操作数

m行，代表具体的操作，字符i表示插入，字符p表示pop弹出

输出

两行，第一行输出栈内元素，第二行输出队列中的元素，两个元素间用空格隔开，行尾无空格
*/

#include <iostream>    
using namespace std;
// 链表节点类  
class ListNode {
public:
    int data;
    ListNode* next;
    ListNode(int value) : data(value), next(nullptr) {}
};

// 链表类  
class LinkedList {
protected:
    ListNode* head;
    ListNode* tail;

public:
    LinkedList() : head(nullptr), tail(nullptr) {}

    // 插入元素到链表尾部  
    void insert_tail(int value) {
        ListNode* newNode = new ListNode(value);
        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    //插入元素到链表头部
    void insert_head(int value)
    {
        ListNode* newNode = new ListNode(value);
        if (!head) {
            head = tail = newNode;
        }
        else
        {
            ListNode* temp = head;
            head = newNode;
            head->next = temp;
        }
    }

    // 清理链表，删除所有元素  
    virtual ~LinkedList() {
        while (head) {
            ListNode* toDelete = head;
            head = head->next;
            delete toDelete;
        }
        tail = nullptr;
    }

    // 辅助函数：获取链表头部元素  
    int peek() {
        if (!head) {
            throw std::out_of_range("List is empty!");
        }
        return head->data;
    }

    // 辅助函数：检查链表是否为空  
    bool isEmpty() const {
        return !head;
    }

    // 打印链表元素  
    void print() const {
        ListNode* current = head;
        while (current) {
            std::cout << current->data;
            if (current->next)
                cout << " ";
            current = current->next;
        }
    }
};

// 栈类  
class Stack : public LinkedList {
public:
    //insert
    void insert(int value)
    {
        insert_head(value);
    }
    // 弹出栈顶元素  
    void pop() {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty!");
        }

        int value = head->data;
        ListNode* nodeToPop = head;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr; // 如果弹出的是最后一个元素，更新尾指针  
        }
        delete nodeToPop;

      
    }
};

// 队列类  
class Queue : public LinkedList {
public:
    //insert
    void insert(int value)
    {
        insert_tail(value);
    }
    // 出队  
    void pop() {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty!");
        }

        int value = head->data;
        ListNode* nodeToDequeue = head;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr; // 如果弹出的是队列中唯一的元素，更新尾指针  
        }
        delete nodeToDequeue;


    }
};

int main() {
    int n;
    cin >> n;
    Stack s;
    Queue que;
    for (int i = 0; i < n; i++)
    {
        int temp;
        cin >> temp;
        s.insert(temp);
        que.insert(temp);
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        char temp;
        cin >> temp;
        if (temp == 'p')
        {
            s.pop();
            que.pop();
        }
        if (temp == 'i')
        {
            int t;
            cin >> t;
            s.insert(t);
            que.insert(t);
        }
    }
    s.print();
    cout << endl;
    que.print();
    cout << endl;
    return 0;
}