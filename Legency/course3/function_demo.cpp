//function_demo.cpp
#include "function_demo.h"
#include "extern_demo.h"

int main(){ 
    float p,q;
    cout<<"Input parameters p,q: ";
    cin>>p>>q;
    cardan(p,q);
    cardan_v2(p,q);
    cout<<endl;
    int a=1,b=2;
    add(a,b)=5;
    cout<<"a="<<a<<", b="<<b<<endl;
    cout<<"t="<<t<<endl;
    return 0;
}
