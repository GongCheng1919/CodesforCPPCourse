## 字符串操作（oj）
程序输入一个字符串，将字符串内的字符全变为大写并输出,样例中的字符串可能有空格
要访问string类型中的第i个字符可以用str[i-1]来访问，即str[0]代表字符串中的第一个字符，角标比第几个字符的字符编号小1，str[i]= 可以将字符串中的某个字符赋成其他值
参考代码：
```
#include<iostream>
#include<string>
using namespace std;
int main()
{
  string input;
  getline(cin,input);
  for(int i=0;i<input.size();i++)//遍历字符串
  {
    if(在这里填条件) 如果满足条件，执行什么代码
  }
  cout<<input;
  return 0;
}
```
**样例输入1**
```
yuanshen! QIDONG! dengdengdengdengdengdeng
```
**样例输出1**
```
YUANSHEN! QIDONG! DENGDENGDENGDENGDENGDENG
```
**样例输入2**
```
crazy Thursday vivo 50
```
**样例输出2**
```
CRAZY THURSDAY VIVO 50
```
**样例输入3**
```
HAppy NeWyEaR
```
**样例输出3**
```
HAPPY NEWYEAR
```
**样例输入4**
```
!@#$%^&*()_+|}{":?><
```
**样例输出4**
```
!@#$%^&*()_+|}{":?><
```
**样例输入5**
```
I am a furry!
```
**样例输出5**
```
I AM A FURRY!
```
