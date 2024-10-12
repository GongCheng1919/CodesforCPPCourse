# C++基本数据类型与存取
## 数据存储与编码
#### 起始地址
-  计算机中的内存是线性编码的，每一个数据和指令都一起存储在内存中的某一位置，并且以某一地址作为起始地址。
-  在32位计算机/程序中，起始地址是一个32位的五符号整数。
```
#include <iostream>
int main() {
int localVar = 42;
int myArray[5] = {1, 2, 3, 4, 5};
std::cout << "Local variable's address: " << &localVar << std::endl;
std::cout << "Array's address: " << myArray << std::endl;
return 0;
```
> Local variable's address: 0x16dc8f008  Array's address: 0x16dc8f010
---
#### 数据长度
- 数据需要占用一定的存储空间。
- 现代计算机使用二进制进行数据表示和存储，其基本单位是位（binary）。
- 位是一个极小的单位，表示一个0/1值。现代计算机体系结构中通常以8位为一个单位，表示一个字节（Byte）。
- C++中，我们通常说某种变量占用多大内存，指的是字节数，比如int通常具有4B这么大。
- 数据的长度对应是数据的内存占用，指的是从数据起始地址开始，存储数据的所需要的连续的内存占用空间。
- C++中可以使用sizeof符号或者对应类型或者变量的内存占用大小（为什么对应类型也可以看大小呢？）。
---
#### 存储内容
-  计算机的内存是一维线性连续的，确定起始地址和数据长度，就可以确定数据的存储位置，获取存储内容。
-  现代计算机使用二进制表示数据，任意数据和指令的存储内容都是二进制的数据。
-  那么怎么区分不同的数据呢？
---
#### 编码格式
- 编码格式指我们怎么编码数据以及解码对应的二进制存储内容。
- C++中使用变量类型来隐式地指明数据的编码、解码和存储的格式和算法。
- 因此，C++中的数据类型非常重要。
---
## 基本数据类型与派生类型
#### 基本数据类型
- 写程序主要是对数据进行计算或处理，也是就是使用 C++语言支持的数据类型和运算，完成计算任务。
- 如下的两个程序分别列出来两种不同的计算程序，分别涉及了计算符号和数据类型的定义
```
#include<iostream>
using namespace std;
int main()
{
  int a,b,sum;
  a=43;
  b=37;
  sum=a+b;
  cout<<"the sum is "<<sum;
  cout<<endl;
}
```
```
#include<iostream>;
int main(){
  const float pai = 3.14;
  float radius;
  cout<<"Enter radius";
  cin>>radius;
  float area=pai*radius*radius;
  cout<<"\n the area of circle is ";
  cout<<area<<endl;
  return 0;
}
```
- 类型的信息决定了**变量值的表示方法**以及**所需的内存量**，类型的信息还决定了相关的算术运算的意义。
- 类型概念的几个要点是：
    - **每一项数据应惟一地属于某种类型。**
    - **每一数据类型意味着一个有明确定义的值的集合。**
    - **同一类型的数据占用相同大小的存储空间。**
    - **同一类型的数据具有相同的（允许对其施加的）运算操作集。**
- C++程序中的数据类型可以分为如下几类
  - 系统提供：
    - 基本类型：int,float,double,char,bool,void
    - 派生类型：（修饰符+基本类型）
  - 用户定义：
    - 完全由用户定义：class，struct,union
    - 部分由用户定义：enum（int的子集）
  - 由其他类型导出：array，struct，pointer，reference
- 基本类型是具有下面 3 个特征的数据类型：
  - 由系统**定义和提供**。
  - 它们是**构造所有其他类型的原始出发点**。
  - 它们是几乎所有程序设计语言都包含的数据类型。
- C++语言的基本数据类型有：int 型、float 型、double 型、char 型、bool型和 void 型。
---
#### 整型
- C++中的整型指的是可以精确表示的整数，其对应于数学中的自然数集合，但是受限于位宽，整型的表示范围通常有限。
- 整型不只可以表示整数，还可以表示离散的状态等等。因此，C++中将整型进一步划分为以下类型：
  - int
  - bool
  - char
  - enum
  - pointer
  - ……
- int 型又称整型。是最常用最基本的数据类型。
  - **范围**：原则上是所有整数，实际的值集为计算机所能表示的所有整数。这个范围是有限的，因此程序员在编程时必须经常考虑因数据过大而溢出的问题。
  - **存储**：占用的存储空间按不同的计算机和编译系统而有所差别，目前在PC 机上运行的各种 C++语言规定 int型数据占用 4 B即 32 bit 空间。
  - **运算**：int 型数据允许算术运算、关系运算等许多种运算。
- char 型又称字符型，即把单个字符作为一种数据处理。
- char 型的值集是全部基本字符、ASCII 码集或扩充的 ASCII 码集对应的全部符号。
- char 型的数据占用**1 B即 8 bit**空间。
- 在作为数字计算的时候，char 型数据与低位宽的 int 型等价，因此可参加的运算相当广泛。
- 字符集可与单字节整数有完整的对应关系（ASCII 码），因此还可把 char 型看做是可以用来表示单字节整数的字符型。
- bool 型在新版的 C++语言中被列为基本类型，它只有两个值：false、true，表示逻辑的真和假，可参加逻辑运算和作为逻辑表达式及关系表达式的结果。bool型的存储空间为**1B，即8bit**。
- bool只能参与逻辑运算。
- bool本身只有0/1两种表示，实际上只需要1bit存储就可以了，为什么在C++中也要将bool存储为8bit的值呢？
- void 型称为无值型。void 型是一种较为抽象的概念，在 C++语言中它用来说明函数及其参数，没有返回值的函数说明为 void 类型的函数，没有参数的函数其形参表由void 表示。
- 有了 void 类型，C++语言规定，所有函数说明（main 函数除外）都必须指明（返回）类型，都必须包含参数说明
---
#### ASCII表
- 计算机本身不能直接区分不同的字母、数字或特殊符号，它是根据每个符号对应的编码来识别这些基本符号的。这些符号的编码表称为ASCII码表。
- ASCII 是美国标准信息交换码（American Standard Code for Information Interchange）的英文缩写，ASCII 码表把 95 个基本（可打印）符号和 33 个控制字符共 128 个字符与 7 位二进制数 0000000～1111111 共 128 个数码建立了对应关系，实际上任何一个基本符号在计算机内的表示形式就是这样一个二进制数码。
---
![ASCII码表](https://img2022.cnblogs.com/blog/2331684/202208/2331684-20220823105506371-1348256748.png)
---
#### 浮点型
- C++中的浮点型对应于数学中的实数类型，因此在许多书和编程语言中浮点又被称为实数型。但是受限于表示位宽，浮点的表示范围和精度通常有限。
- C++中实现了IEEE754标准的浮点类型：
  - double
  - float
- 浮点表示通常是不精确的，比如1.3这个实数通常难以在计算机中获得精确的1.3的表示，因此对浮点数做操作时，通常用作数学计算，不做条件判定。
- float 型又称浮点型，它对应着数学中的实数概念，带小数点的数。
- float 型的值集，原则上是任意大小和精度的小数，实际的值集虽然不可能是任意大小，但由于采用尾数+阶码的表示形式，所以其可表示浮点数的范围可大到**±3.4*10^38** , 表示的精度可以小到**1.0*10^-38**。因此，在一般的应用问题中，float 型数据总是可以满足精度和大小的要求，不会出现溢出现象。
- float 型数据一般占用 **4 B**，即 **32 bit** 空间。当精度较高或数值较大时，人们往往使用 double型（占用 **8 B**，即 **64 bit** 空间）。
- float 型数据与 int 型数据的区别在于它们所参加的运算操作类型是不同的。比如增减量运算（++，––），条件判断等语句中。
---
![IEEE754](https://img-blog.csdnimg.cn/2fe77afa39804122952ba059fdee86b3.png)
---
#### 派生类型及关键字
- 基本类型经过简单的字长及范围放大或缩小，就形成了基本类型的简单派生类型。
- 派生类型的说明符由 int、float、double、char 前面加上类型修饰符组成。类型修饰符包括：
  - short：短的，缩短字长。
  - long：长的，加长字长。
  - signed：有符号的，值的范围包括正负值。
  - unsigned：无符号的，值的范围只包括正值。
---
![派生类型及关键](https://img-blog.csdnimg.cn/20190110115017898.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjE2Nzc1OQ==,size_16,color_FFFFFF,t_70)
---
#### 数据类型的内存量
```
#include<iostream>
using namespace std;
int main()
{
  cout<<"sizeof(int)="<<sizeof(int)<<endl;
  cout<<"sizeof(float)="<<sizeof(float)<<endl;
  cout<<"sizeof(double)="<<sizeof(double)<<endl;
  cout<<"sizeof(wchar_t)="<<sizeof(wchar_t)<<endl;
  cout<<"sizeof(char)="<<sizeof(char)<<endl;
  cout<<"sizeof(bool)="<<sizeof(bool)<<endl;
  return 0;
}
```
run
```
sizeof(int)=4
sizeof(float)=4
sizeof(double)=8
sizeof(wchar_t)=2
sizeof(char)=1
sizeof(bool)=1
```
---
## 数据大小与类型转换
#### sizeof
-  sizeof是C++中的一个不可重载运算符，通常用于动态内存分配，其在底层具有重要作用，不可重载；
- sizeof接受类型参数或者变量，返回类型或者变量占用的内存大小（以字节byte为单位）；
- sizeof和取地址运算结合，可以获取任意变量的数据存储区域（起始地址+数据长度），可以实现许多底层数据操作。
```
int arr[5] = {1, 2, 3, 4, 5};
std::cout << "Size of int: " << sizeof(int) << " bytes" << std::endl;
std::cout << "Size of double: " << sizeof(double) << " bytes" << std::endl;
std::cout << "Size of char: " << sizeof(char) << " bytes" << std::endl;
std::cout << "Size of arr: " << sizeof(arr) << " bytes" << std::endl;
```
#### 不同类型的大小
- 基本数据类型
  - 整型和浮点
- 基本数据类型的派生类型
  - short/long/signed/unsigned
- 导出类型
  - 数组
  - 指针
  - 引用
- 自定义数据类型：
  - 枚举
  - 结构
  - 联合
  - 类
 ---
 #### 强制类型转换
 - C语言中支持不同类型间的强制类型转换：
 - 这种显式的强制的类型转换可能会进行数据的重新编码，取决于编译器支持，并不一定是安全的，可能出现错误。比如整型10到浮点10.0的转换。
- 另一种更直接的强制类型转换是仅进行指针类型转换：
```
int a = 10;
float b = a;
double c = (double)a;
```
- 另一种更直接的强制类型转换是仅进行指针类型转换：
-  这种转换不会改变数据的编码方式，仅仅修改数据的类型，因此需要称需要自己决定是否转换，以及转换后的结果，一般而言是不安全和不推荐的，但是可以实现更基础更底层的操作。
```
int a = 10;
float b = *(float*) &a;
double c = *(double*) &a;
```
---
#### 安全的类型转换
- C++中的显式类型转换：
  - static_cast & dynamic_cast
  - const_cast
  - reinterpret_cast
- static_cast：
  - 用于进行常见的类型转换，如数值类型之间的转换、继承关系中的类型转换等。
  - 在**编译**时进行类型检查，不会进行运行时的类型检查。
  - 在转换时，程序员需要确保转换是合法和安全的。
- dynamic_cast:
  - 常用于在继承关系中进行类型转换，用于检查在运行时是否能够安全地将指针或引用转换为目标类型。
  - 会进行**运行时**的类型检查，如果类型转换不合法，会返回异常。
  - 只能用于具有虚函数的类之间的转换，用于安全地在派生类和基类之间进行转换。
- const_cast：
  - 通常用于消除函数参数的 const 修饰符，以便在函数中修改参数的值。
- reinterpret_cast:
  - 不改变指针和内存位置，但是将重新解释当前指针指向的内存区域的读取方式。
  - 类似于强制的指针类型转换。
  - 对于不同类型之间的转换，没有任何类型检查或安全性保障
  ---
#### C++ 基本数据类型与存取
```
#include <iostream>
#include <cstring>
int main() {
// 定义并使用不同的基本数据类型
int integerVar = 42;
float floatVar = 3.14f;
double doubleVar = 3.141592653589793;
char charVar = 'A';
std::string stringVar = "Hello, C++!";
// 观察不同数据类型在内存中的大小和起始地址
std::cout << "Size of int: " << sizeof(integerVar) << " bytes. Address: " << &integerVar << std::endl;
std::cout << "Size of float: " << sizeof(floatVar) << " bytes. Address: " << &floatVar << std::endl;
std::cout << "Size of double: " << sizeof(doubleVar) << " bytes. Address: " << &doubleVar << std::endl;
std::cout << "Size of char: " << sizeof(charVar) << " byte. Address: " << (void*)&charVar << std::endl;
std::cout << "Size of string: " << sizeof(stringVar) << " bytes. Address: " << &stringVar << std::endl;
return 0;
}
```
---
```
#include <iostream>
#include<cstring>
int main() {
// 定义并使用不同的基本数据类型
int integerVar = 42;
float floatVar = 3.14f;
double doubleVar = 3.141592653589793;
char charVar = 'A';
std::string stringVar = "Hello, C++!";
// 实现对字符串型数据的操作
std::string newString = stringVar + " How are you?";
std::cout << "New string: " << newString << std::endl;
// char*类型字符串操作
char* charPtr = "Old char* string";
char newCharPtr[50];
strcpy(newCharPtr, charPtr);
strcat(newCharPtr, " Added text.");
std::cout << "New char* string: " << newCharPtr << std::endl;
return 0;
}
```
---
```
#include <iostream>
#include <cstring>
int main() {
// 定义并使用不同的基本数据类型
int integerVar = 42;
float floatVar = 3.14f;
double doubleVar = 3.141592653589793;
char charVar = 'A';
std::string stringVar = "Hello, C++!";
// 分析数据的解码方式（类型转换）对程序结果的影响
int intFromDouble = static_cast<int>(doubleVar);
std::cout << "Double " << doubleVar << " converted to int: " << intFromDouble << std::endl;
return 0;
}
```
## 课后习题
- 字符串操作——stringoperator.cpp，字符串操作.md
- 探究不同数据类型的大小——testsize.cpp，探究不同数据类型的大小.md
- 数据类型的探究——testdataclass.cpp，数据类型的探究.md
- 类型转换对程序的影响——testchange.cpp，类型转换对程序的影响.md
  










