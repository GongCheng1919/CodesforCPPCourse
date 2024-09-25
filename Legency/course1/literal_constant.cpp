// literal_constant.cpp
#include <iostream> 
using namespace std;
int main(void)
{
    int radiu = 4;
    float pai = 3.1415926535;
    float weight = 6.9e4;
    const char* str = "Hello World! \nHello China! \0 Hello Nankai\n";
    cout<<" radiu = "<<radiu<<"\n pai = "<<pai<<"\n weight = "<<weight<<"g\n";
    cout<< str<<endl;
    return 0;
}
