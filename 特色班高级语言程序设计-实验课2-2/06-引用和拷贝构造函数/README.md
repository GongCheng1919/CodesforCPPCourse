# 课程内容
## 引用
引用变量是一个别名，也就是说，它是某个已存在变量的另一个名字。一旦把引用初始化为某个变量，就可以使用该引用名称或变量名称来指向变量。[菜鸟教程 引用](https://www.runoob.com/cplusplus/cpp-references.html)

值得注意的是，引用型参数在函数被调用时，相应的实参必须是对应类型的变量或对象
#### **拷贝构造函数**
拷贝构造函数通过从相同类型的对象复制成员值来初始化对象。

如果类成员都是简单类型（如标量值），则编译器生成的拷贝构造函数已够用，你无需定义自己的函数。 

如果类需要更复杂的初始化，则需要实现自定义拷贝构造函数。拷贝构造函数 **只含有一个形参**，而且其形参为本类对象的引用。

```cpp
	Box(Box& other); // Avoid if possible--allows modification of other.
	Box(const Box& other);
	
    // Additional parameters OK if they have default values
    Box(Box& other, int i = 42, string label = "Box");
```

拷贝构造函数的三个调用时机：
>1. 使用一个已经创建的对象来初始化一个新的对象
>2. 值传递的方式给函数传值
>3. 值方式返回局部对象
#### 移动构造函数
C++ 11 引入的移动构造函数是特殊成员函数，它将现有对象数据的所有权移交给新变量，而不复制原始数据，此后原对象将被摧毁。 它采用 `rvalue` 引用作为其第一个参数，以后的任何参数都必须具有默认值。 移动构造函数在传递大型对象时可以显著提高程序的效率。

```cpp
Box(Box&& other);
```

#### **赋值构造函数**
赋值构造函数是一种通过重载赋值运算符 `=` 来实现类对象之间的赋值初始化的特殊的构造函数。在进行类对象之间的赋值时，会自动调用赋值构造函数进行对象间赋值。

如果不声明复制构造函数，编译器将为你生成成员的复制构造函数。 同样，如果不声明复制赋值运算符，编译器将为你生成成员的复制赋值运算符。 声明复制构造函数不会取消编译器生成的复制赋值运算符，反之亦然。

```cpp
// spec1_copying_class_objects.cpp
class Window
{
public:
    Window( const Window& );            // Declare copy constructor.
    Window& operator=(const Window& x); // Declare copy assignment.
    // ...
};
```
# 实验题目
## reandcopy - 动态拼接数组
实现一个动态数组类，并实现函数用于拼接和合并（先排序再合并）任何两个动态数组对象，要求重载 `+` 和 `||` 来实现

