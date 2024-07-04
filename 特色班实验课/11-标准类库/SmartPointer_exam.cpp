#include <iostream>
using namespace std;

template<typename T>
class SmartPointer {
private:
    T* ptr;              // 指向动态分配的对象的指针
    int* ref_count;     // 引用计数指针

public:
    // 空构造函数
    SmartPointer() {
        cout<<"SmartPointer Constructor"<<endl;
        cout<<"create a new smart pointer"<<endl;
        // Your code here
    }

    // 常规构造函数
    explicit SmartPointer(T* p) {
        cout<<"SmartPointer Constructor"<<endl;
        cout<<"create a new smart pointer"<<endl;
        // Your code here
    }

    // 拷贝构造函数
    SmartPointer(const SmartPointer<T>& other){
        cout<<"SmartPointer Constructor"<<endl;
        // Your code here
    }

    // 赋值运算符重载
    SmartPointer<T>& operator=(const SmartPointer<T>& other) {
        cout<<"Assignment Operator"<<endl;
        // Your code here



        return *this;
    }

    // 赋值运算符重载（指针类型）
    SmartPointer<T>& operator=(T* newPtr) {
        cout<<"Assignment Operator"<<endl;
        // Your code here


        return *this;
    }

    // 重载*运算符
    T& operator*() const { return *ptr; }
    T& operator[](int i) const { return ptr[i]; }

    // 析构函数
    ~SmartPointer() {
        cout<<"Deconstructor"<<endl;
        if (ptr) {
            cout<<"decrease ref_count ["<<*ref_count<<"] by 1"<<endl;
            (*ref_count) --;
            // Your code here


        }
    }
};

template<typename T>
class TestClass {
public:
    SmartPointer<T> sp;  // 智能指针数据成员
    // 常规构造函数
    TestClass(SmartPointer<T> p) : sp(p) {}

    // 拷贝构造函数
    TestClass(const TestClass& other) : sp(other.sp) {}

    // 赋值运算符重载
    TestClass& operator=(const TestClass& other) {
        if (this != &other) {
            sp = other.sp;
        }
        return *this;
    }
};

int main() {
    int n;
    cin>>n;
    SmartPointer p = SmartPointer(new int[n]);
    for (int i = 0; i < n; ++i) {
        int m;
        std::cin>>m;
        p[i] = m;
    }

    TestClass<int>* TCPtr[10];
    for (int i = 0; i < n; ++i) {
        TCPtr[i] = new TestClass<int>(p);
        TCPtr[i]->sp[i] *= i;  
    }
    for (int i = 1; i < n; ++i) {
        // check here
        TCPtr[i] = TCPtr[i-1];
        TCPtr[i]->sp[i] *= i*(i-1);  
    }
    for (int i = 0; i < n; ++i) {
        delete TCPtr[i];
        TCPtr[i] = nullptr;
    }
    return 0;
}