#include <iostream>

class A {
public:
    virtual void func1() {
        std::cout<<"A::func1() called"<<std::endl;
    }
    virtual void func2() {
        std::cout<<"A::func2() called"<<std::endl;
    }
    virtual void func3() {
        std::cout<<"A::func3() called"<<std::endl;
    }
};

class B : public A {
public:
    void func1() override {
        std::cout<<"B::func1() called"<<std::endl;
    }
    void func2() override {
        std::cout<<"B::func2() called"<<std::endl;
    }
    void func3() override {
        std::cout<<"B::func3() called"<<std::endl;
    }
};

class C : public A {
public:
    void func1() override {
        std::cout<<"C::func1() called"<<std::endl;
    }
    void func2() override {
        std::cout<<"C::func2() called"<<std::endl;
    }
    void func3() override {
        std::cout<<"C::func3() called"<<std::endl;
    }
};

class D : public A {
public:
    void func1() override {
        std::cout<<"D::func1() called"<<std::endl;
    }
    void func2() override {
        std::cout<<"D::func2() called"<<std::endl;
    }
    void func3() override {
        std::cout<<"D::func3() called"<<std::endl;
    }
};

int main() {
    char className;
    int functionNumber;
    std::cin >> className >> functionNumber;

    
    A a, *ptr;
    A* obj;
    using FuncType = void (A::*)();
    int base_offset = 0;

    switch (className) {
        case 'A':
            obj = new A();
            base_offset=0;
            break;
        case 'B':
            obj = new B();
            base_offset+=3*sizeof(ptr);
            break;
        case 'C':
            obj = new C();
            base_offset+=6*sizeof(ptr);
            break;
        case 'D':
            obj = new D();
            base_offset+=9*sizeof(ptr);
            break;
        default:
            std::cout << "Invalid class name" << std::endl;
            return 0;
    }
    ptr = obj;
    FuncType* base_vtable_addr = *(FuncType**)&a;
    FuncType* derived_vtable_addr = *(FuncType**)obj;
    FuncType func = *(FuncType*)(((char*)derived_vtable_addr)+(functionNumber-1)*8);

    std::cout << "Relative address: " << (functionNumber-1)*sizeof(ptr) << std::endl;

    (obj->*func)();

    delete obj;

    return 0;
}