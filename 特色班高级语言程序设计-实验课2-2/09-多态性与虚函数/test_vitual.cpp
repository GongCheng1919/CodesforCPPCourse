#include <iostream>

class WithVirtualFunc {
public:
    int a;
    virtual void func() {
        std::cout << "WithVirtualFunc::func() called" << std::endl;
    }
};

class WithoutVirtualFunc {
public:
    int a;
    void func() {
        std::cout << "WithoutVirtualFunc::func() called" << std::endl;
    }
};

int main() {
    WithVirtualFunc wvf;
    WithoutVirtualFunc wvf_no;

    // 打印虚函数表指针的地址（通常在对象的起始位置）
    std::cout << "Address of vtable pointer in WithVirtualFunc object: " << &wvf << std::endl;
    // 打印对象的起始地址
    std::cout << "Start address of WithVirtualFunc object.a: " << (void*)&wvf.a << std::endl;
    // std::cout << "Start address of WithVirtualFunc object: " << (void*)&wvf.a << std::endl;

    // 对于没有虚函数的类对象，这里不会有vtable指针
    std::cout << "Start address of WithoutVirtualFunc object: " << &wvf_no << std::endl;
    std::cout << "Start address of WithoutVirtualFunc object.a: " << &wvf_no.a << std::endl;

    return 0;
}