// structure-demo.cpp
#include <iostream> 
#include <cstring>
using namespace std;
enum sexType {male,female};
struct Employee {
    char name[20];
    enum sexType sex;
    float salary;
    char phone[12];
};
Employee efile[100];

ostream& operator<<(ostream& out, Employee eple){
    const char* sex= eple.sex?"female":"male";
    out<<"{ name="<<eple.name
       <<", sex="<<sex
       <<", salary="<<eple.salary
       <<", phone="<<eple.phone
       <<" }"<<endl;
    return out;
}

void struct_test(){
    struct Employee gy1,gy2;
    Employee gy3,gy4={"John Smith", male, 2107.5, "02223501234"};
    strcpy(gy3.name,"John");
    gy3.sex=male;
    cin>>gy3.salary>>gy3.phone;
    gy1=gy3;
    gy2=gy4;
    cout<<"gy1"<<gy1<<endl;
    cout<<"gy2"<<gy2<<endl;
}
