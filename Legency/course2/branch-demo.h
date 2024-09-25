// branch-demo.h
#include <iostream>
using namespace std;

void if_test()
{
    int a, b, c, max;
    cout << "first integer:";
    cin >> a;
    cout << "second integer:";
    cin >> b;
    cout << "third integer:";
    cin >> c;
    if (a < b) // 以下 6 行程序用来求最大元
        if (c < b)
            max = b;
        else
            max = c;
    else if (c < a)
        max = a;
    else
        max = c;
    cout << "maximum element: " << max << endl;
}

void switch_test()
{
    float t, tc, tf;
    char corf;
    const float fac = 1.8, inc = 32.0;
    cout << "Enter temperature:";
    cin >> t;    // 输入温度值
    cin >> corf; // 指出是摄氏(c)或华氏(f)
    switch (corf)
    {
    case 'c':
    case 'C':
        tc = t;
        tf = t * fac + inc;
        break;
    case 'f':
    case 'F':
        tf = t;
        tc = (t - inc) / fac;
        break;
    default:
        tc = tf = 0.0;
    }
    cout << "The temperature is:";
    cout << tc << "C=" << tf << "F\n";
}

void find_prime(int m)
{
    int i, j, isprime, count=0;
    for (i = 2; i <= m; i++)
    {   isprime = 1;
        for (j = i - 1; j > 1; j--) // 判断 i是否为素数
            if (i % j == 0)
                isprime = 0; // 用 j(i－1～2)试除 i
        if (isprime){
            cout << i << ",";
            count++;
            if (count % 20 == 0)
                cout << endl;   } }
    cout << endl;
}
