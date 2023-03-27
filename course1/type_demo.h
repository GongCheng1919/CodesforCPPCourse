// type_demo.h
#include <iostream> 
using namespace std;
typedef int studentid;

void sizeoftype(){    
    const float pai = 3.1416;

    const char* str = "Hello C++";

    int size, high, temp= 37;
    static long sum;
    auto tt = 0.5;

    cout<<"sizeof(int)="<<sizeof(int)<<endl;
    cout<<"sizeof(float)="<<sizeof(float)<<endl;
    cout<<"sizeof(double)="<<sizeof(double)<<endl;
    cout<<"sizeof(wchar_t)="<<sizeof(wchar_t)<<endl;
    cout<<"sizeof(char)="<<sizeof(char)<<endl;
    cout<<"sizeof(bool)="<<sizeof(bool)<<endl;
}

void acm_variable(){
    float acm = 0.0;
    acm+=1;
    cout<<"acm_variable.acm = "<<acm<<endl;
}

void acm_static(){
    static float acm = 0.0;
    acm+=1;
    cout<<"acm_static.acm = "<<acm<<endl;
}
