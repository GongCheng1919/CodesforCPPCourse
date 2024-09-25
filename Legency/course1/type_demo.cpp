// type_demo.cpp
#include "type_demo.h"

// int global_a = 0;
int global_a=0;
extern int global_a;
extern int global_a;
namespace name1{
    int i,j,k;
}
namespace name2{
    int i,j,k;
}


typedef int studentid;
int main(void)
{
    studentid gongcheng = 1210517;
    cout<<"gongcheng's id = "<<gongcheng<<", sizeof(studentid)="<<sizeof(studentid)<<endl;

    name1::i = 1;
    name1::j = 2;
    name1::k = 3;
    name2::i = 4;
    name2::j = 5;
    name2::k = 6;

    register float cum = 0.0;
    for(int i=0;i<1000;i++){
        cum +=i;
    }

    for(int i=0;i<5;i++){
        acm_variable();
        acm_static();
    }

    int local_a = 1;
    {
        float local_a = 2.0;
        cout<<"global_a="<<global_a<<", local_a="<<local_a<<endl;
    }
    sizeoftype();
    cout<<"global_a="<<global_a<<", local_a="<<local_a<<endl;
    return 0;
}
