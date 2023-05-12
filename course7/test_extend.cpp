#include<iostream>
using namespace std;

class A{
    public:
    int name;
    static int a;
    int* p;
    A(){
        p = new int[10];
    }
    A(A& a){
        p = new int[10];
        for(int i=0;i<10;i++){
            p[i] = a.p[i];
        }
    }
};
int A::a = 0;
class B: public A{
    public:
    int name;
    static int b;
    int* q;
    B(){
        q = new int[10];
        this->name = 1;
        this->A::name = 2;
    }
};
int B::b = 0;

class A{бн}; 
class B: virtual public A{бн}; 
class C: virtual public A{бн};
class D: public B, public C{бн};



int main(){
    B b1;
    cout<<b1.name<<","<<b1.A::name<<endl;
    B b2(b1);
    cout<<b1.p<<"=?"<<b2.p<<endl;
    cout<<b1.q<<"=?"<<b2.q<<endl;
    A a;
    b2.a=10;
    cout<<a.a<<","<<b2.a<<endl;
    return 0;
}



