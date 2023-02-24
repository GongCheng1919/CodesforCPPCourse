//program 3-2.cpp
#include<iostream>
using namespace std;
int main()
{
    const float pai = 3.14;
    float radius;
    cout <<" Enter radius:";
    cin >> radius;
    float area = pai * radius * radius;
    cout << "\n The area of circle is ";
    cout << area << endl;
    return 0;
}
