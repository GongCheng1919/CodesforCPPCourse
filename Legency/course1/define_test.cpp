//define_test.h
#include<iostream>
using namespace std;
#define YES 1
#define PI 3.14159
#define RAD PI/180
#define BEGIN {
#define END }
#define MAIN main
#define PRT1 cout<<"\n The Begin "
#define Max(a,b) (a>b?a:b)
#define REGISTER
#define ZERO 0.000001
#undef ZERO
#define ZERO 0.001
#define MUL(a,b) a*b
int MAIN(void)
BEGIN
    PRT1<<"max value = "<<Max(12,3);
    PRT1<<"ZERO = "<<ZERO;
    PRT1<<"MUL(2,3+4) = "<<MUL(2,3+4);
    cout<<endl;
    return 0;
END

