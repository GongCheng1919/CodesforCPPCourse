#include<iostream>
using namespace std;
int main()
{
    double volume;
    int height, radius;
    cin >> height >> radius;
    volume = 3.14 * radius * radius * height;
    cout << int(20000 / volume) + 1;
    return 0;
}