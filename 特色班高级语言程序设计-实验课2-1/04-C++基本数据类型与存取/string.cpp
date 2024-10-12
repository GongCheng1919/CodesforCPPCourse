#include<iostream>
#include<string>
using namespace std;
int main()
{
    string input;
    getline(cin, input);
    for (int i = 0; i < input.size(); i++)//遍历字符串
    {
        if (input[i] >= 'a' && input[i] <= 'z') input[i] -= 'a' - 'A';
    }
    cout << input;
    return 0;
}
