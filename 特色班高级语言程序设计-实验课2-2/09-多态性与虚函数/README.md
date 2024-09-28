# 课程内容
函数超载 虚函数
## 函数超载
- C++允许在不同的类中出现其**原型完全相同的函数**，即所谓的函数超载。
- 仅在基类与其派生类的范围内实现（与使用）。
- 允许（支持）多个不同函数（的实现）使用完全相同的函数名、函数参数表以及函数返回类型。
-  通常这些函数是语义相近的或完全相同的（仅具体实现方法即实现代码不同）。
-  基类和派生类中的函数超载可能存在二义性。
-  根据虚函数定义，函数超载二义性可由虚函数处理。
---
## 虚函数
- 在定义某一基类（或其派生类）时，若将其中的某一个非静态成员函数的属性说明为 virtual，则称该函数为虚函数。其一般说明形式为：
> virtual <返回类型><函数名>（<参数表>）{…};
- 虚函数的使用与函数超载密切相关。若基类中某函数被说明为虚函数，则意味着其派生类中也要用到与该函数同名、同参数表、同返回类型，但函数（实现）体不同的同一个超载函数。
- 在编译阶段系统无法判断此次虚函数调用应执行哪一段函数代码。只有到了运行过程执行到此处时，才能临时判断应执行哪一段函数代码，对虚函数的这种处理方式称为**动态联编（dynamic banding）**。
- 虚函数的机制要点为：
- - 在基类 CB中说明某一函数成员 f()为虚函数，方法是在说明前加关键字“virtual”。如 virtual void draw()；
  - 在 CB的各个派生类 CD1，CD2，…，CDn 中定义与f()的原型完全相同（但函数体可以各异）的函数成员 f()，无论是否用关键字 virtual来说明，它们都自动地被定义为**虚函数**，即**派生类中虚函数处的关键字 virtual可以省略，但基类处不可省。**
  - 当在程序中采用**以 CB 类指针 pb 的间接形式调用函数 f()，即使用 pb->f()时，系统对其将采用动态联编的方式进行处理。**
- 虚函数的实现原理
- - 虚函数是C++类中的成员函数，它允许派生类提供特定的实现。当一个类中至少有一个虚函数时，编译器会为这个类创建一个虚函数表。
  - 虚函数表是一个存储函数指针的数组，每个包含虚函数的类都有一个。虚函数表中存储了类中所有虚函数的地址。
  - 当通过基类指针或引用调用一个虚函数时，程序实际上使用的是动态联编。编译器生成的代码**首先会查找对象内部的虚函数表指针，然后根据这个指针找到虚函数表，并在表中查找对应的函数指针来执行。（这意味着又虚函数的类对象会大一些）**
  - 由于虚函数表的存在，程序可以在运行时识别对象的实际类型，即使对象是通过基类类型的指针或引用访问的，即使通过基类指针调用函数，如果对象实际上是派生类的一个实例，也会调用派生类中覆盖的虚函数版本，因为**基类指针调用的虚函数表指针其实是指向派生类的虚函数表的，而不是基类的虚函数表。**
  -  虚函数表在程序启动时由编译器生成，**并存储在程序的只读数据段中**。每个包含虚函数的对象都会有一个虚函数表指针，指向这个类的虚函数表。
```
class graphelem{ // 自定义类 graphelem
protected:
  int color; // 颜色 color
public:
  graphelem(){color = 0;}
  virtual void draw()
  {
  cout <<"graphelem"<< endl;
  }; // 基类中含有一个虚函数

};
class line : public graphelem
{ // 自定义类 line，为基类 graphelem 的派生类
  public: // 虚函数 draw 负责画出“line”
  virtual void draw() { cout << "draw line" << endl; }; 
};
class circle : public graphelem
{ // 自定义类 circle，为基类 graphelem 的派生类
public: // 虚函数 draw，负责画出“circle” 
  virtual void draw(){ cout << "draw circle" << endl; }; 
};
class triangle : public graphelem
{ // 类 triangle，为基类 graphelem 的派生类
public: // 虚函数 draw 负责画出“triangle”
  virtual void draw(){ cout << "draw triangle" << endl; }; 
};
int main()
{
  graphelem *p[3]; // 定义一个指针数组，数组元素为基类 graphelem 的指针
  p[0] = new line(); // 指针数组的第一个元素指向派生类 line 的对象
  p[1] = new circle(); // 指针数组的第二个元素指向派生类 circle 的对象
  p[2] = new triangle(); // 指针数组的第三个元素指向派生类 triangle 的对象
  for (int i = 0; i < 3; i++)
    p[i]->draw(); // 调用指针数组中各个元素的 draw() 函数
  return 0;
}
```
-  虚函数和重载函数的区别和联系：
-  - 它们都是在程序中设置一组**同名函数，都反映了面向对象程序中的多态性特征；**
   - 虚函数**不仅同名，而且同原型；**
   - 虚函数**仅用于基类和派生类之中，不同于函数重载，可以是类内或类外函数；**
   - 虚函数在程序运行时**动态联编以确定具体函数代码，而重载函数在编译时即可确定**
   - 虚函数**一般是一组语义相近的函数，而函数的重载，相互之间可能是语义无关的。**
   - **构造函数不能说明为虚函数，但是构造函数通常有许多重载函数**。这是因为构造函数的调用一般出现在对象创建的同时或之前，这时无法用指向其对象（尚未创建）的指针来引用它。
   - **析构函数可以说明为虚函数，此时这一组虚函数的函数名是不同的**。当在析构函数中采用基类指针释放对象时，应注意把析构函数说明为虚函数，以确定释放的对象
---
## 纯虚函数与抽象基类
- 如果不准备在基类的虚函数中做任何事情，则可在虚函数的原型后加上“=0”字样替掉函数定义体（没有具体的实现），则这样的虚函数称为纯虚函数。
> virtual <函数原型>= 0;
- 纯虚函数只为其派生类的各虚函数规定了一个一致的“原型规格”，该虚函数的实现将在它的派生类中给出。
- **含有纯虚函数的基类称为抽象基类。注意，不可使用抽象基类来说明并创建它自己的对象**，只有在创建其派生类对象时，才有抽象基类自身的实例伴随而生。
- 抽象基类中的虚函数使基类作为这一组类的抽象，**基类成为它的若干派生类的对外接口**。通过抽象基类，再“加上”各派生类的特有成员以及对基类中那一纯虚函数的具体实现，可以构成一个具体的实用类型。
- 许多引入虚函数的程序，把基类的虚函数说明为纯虚函数，从而使基类成为一种抽象基类，可以更自然地反映实际应用问题中对象之间的关系。
- **如果一个抽象基类的派生类中没有定义基类中的纯虚函数**，而只是继承了基类的纯虚函数，则**这个派生类还是一个抽象基类**，其中仍包含着继承而来的那个纯虚函数。

以下是纯虚函数的一个例子，是特色班期末考试笔试的一道题
题目的大致要求：建立一个缓冲区抽象基类，再建立两个类继承该基类，其中一个类在缓冲区内容满后将内容输出到屏幕上，另一个类在缓冲区满后将内容输出到文件里
```
#include<iostream>
#include<sstream>
#include<fstream>
using namespace std;
class Buffer
{
protected:
	int capacity=20;//缓冲区内最大容量
	stringstream buffer;//缓冲区
	virtual void clean_output() = 0;//将缓冲区清空并输出到对应位置的虚函数
public:
	void updata(stringstream& input);//更新缓冲区的函数
};
class fileoutput : public Buffer
{
private:
	string filename;//文件名
	virtual void clean_output() override;
public:
	fileoutput(string file) :filename(file) {}
};
class screenoutput :public Buffer
{
private:
	virtual void clean_output() override;
};
void Buffer::updata(stringstream& input)//负责将外部数据读入缓冲区，如果缓冲区内数据超过最大容量则按照不同类的对应方式输出
{
	string str;
	while (getline(input, str))
	{
		buffer << str;
		buffer << endl;
	}
	if (buffer.str().size() > capacity) {
		clean_output(); buffer.str(""); buffer.clear();
	}
	input.str("");
}
void fileoutput::clean_output()//将缓冲区清空并且把缓冲区的内容读入某个文件中
{
	fstream fst(filename,std::fstream::out) ;
	if (fst.is_open())
	{
		string str;

		while (getline(buffer, str))
		{
			fst << str;
			cout << str;
		}
	}
	fst.close();
}
void screenoutput::clean_output()//将缓冲区清空并且将缓冲区的内容打在屏幕上
{
	string str;
	while (getline(buffer, str))
	{
		cout << str << endl;
	}
}
int main()
{
	string str;
	getline(cin, str);
	cin.ignore();
	fileoutput testfile("test.txt");
	stringstream ss(str);
	testfile.updata(ss);
	ss.str(str);
	screenoutput testscreen;
	testscreen.updata(ss);
	return 0;
}
```
在该代码中，两个类通过this指针在updata函数里分别调用两类自己的clean_output函数，很多初学者在学习虚函数和多态性的时候认为该知识点难以理解，老师给的例子也十分抽象，但通俗来理解，多态性实现了各个类调用同名的，有类似作用的，从基类继承来的虚函数。意思也就是说，即使在基类的某个函数中写道调用基类中的某个虚函数，但若是在派生类中继承并重写了该函数，则使用派生类的该函数。基类便相当于一个平台，将不同派生类的共性封装起来，而多态性则保证了不同派生类在共性的行为里保持了自己的个性。继承同一基类的各个派生类必然有一些相似的操作，然而这些操作并不完全相同，此时便可通过虚函数来实现各个派生类对于这些操作自己的定义
# 实验题目
## calc_shape——虚函数：计算几何图形的面积和周长
在一个二维平面上，有许多不同的几何形状，包括圆形、矩形和三角形。每种形状都有自己的面积和周长。你的任务是创建一个形状类（Shape）和三个派生类（Circle，Rectangle，Triangle），并实现两个虚函数 calculateArea() 和 calculatePerimeter()，这两个函数会返回形状的面积和周长。

要求：

Shape类应该有两个虚函数calculateArea和calculatePerimeter，这两个函数应该返回double类型的值。
Circle，Rectangle，Triangle类应该从Shape类派生，并且应该重写calculateArea和calculatePerimeter函数。
Circle类应该有一个名为radius的成员变量，Rectangle类应该有两个名为width和height的成员变量，Triangle类应该有三个名为a，b，c的成员变量，分别代表三边的长度。
每个类应该有一个接受相应成员变量作为参数的构造函数，该构造函数应该设置相应的成员变量的值。
输入： 第一个参数为Circle，Rectangle，Triangle中的一个字符串，接下来多个浮点数，表示对应类型的参数

输出：几何图形的面积和周长
## Functions，AutoGrad——虚函数：实现自动求导算子基类Function
[实现原理]([特色班高级语言程序设计-实验课2-2/09-多态性与虚函数/AutoGrad.md](https://github.com/GongCheng1919/CodesforCPPCourse/blob/master/%E7%89%B9%E8%89%B2%E7%8F%AD%E9%AB%98%E7%BA%A7%E8%AF%AD%E8%A8%80%E7%A8%8B%E5%BA%8F%E8%AE%BE%E8%AE%A1-%E5%AE%9E%E9%AA%8C%E8%AF%BE2-2/09-%E5%A4%9A%E6%80%81%E6%80%A7%E4%B8%8E%E8%99%9A%E5%87%BD%E6%95%B0/AutoGrad.md))

为了实现这个功能，你可能需要完成：

1. 首先你需要实现一个Tensor类，用于存储张量的数据。为了测试简单，请你用随机数生成器来生成数据填充，随机算法为std::mt19937，种子为0，类型float，范围0.0到1.0
2. 基于Tensor类，你需要实现一个GradTensor类用于Function的前向传播和累积反向传播中的梯度。GradTensor为带梯度的Tensor，其相比于普通的Tensor类多了一个Tensor类型的grad成员用于存储和更新梯度。
3. 设计一个可以自动求导的Function基类，其包含forward和backward两组虚函数，分别用于计算函数值和梯度。并且包含一个ctx的成员变量，其是一个vector对象，用于存储GradTensor对象。
4. 实现由Function派生出的Add类和Mul类，分别用于实现GradTensor加法和对位乘法，以及对这两个参数的自动求导。

输入和输出：

输入三个整数[m,n,k]，然后调用Mul和Add类的forward函数用于计算$A*A+A$的结果，你需要分别列出每一步的计算结果。

然后通过Mul和Add类的backward函数，计算$A*A+A$对$A$的梯度。

请参考BP算法和链式求导法则进行反向求导，假设最后层对输出的梯度也为$A$.

记住，如果对$A$有多个梯度，需要将其累加。

输入输出请参考示例，数值类型为float类型。

## test_virtual2 ——虚函数：测试虚函数表
请构建包含3个虚函数（用func1，func2，func3）的基类（用符号‘A’表示），以及base类的3个派生类（符号‘B’,'C','D'表示），要求均实现了基类的3个虚函数。

请打印出派生类对象的虚函数调用地址条目在虚函数表中的相对地址（相对于第一个虚函数的首地址）。

输入：一个字符（A，B，C，D）和一个整数（1，2，3）

输出：输出对应类的实例化对象对应的虚函数调用地址条目在虚函数表中的相对地址，以及该虚函数的调用结果。
## Animal ——虚函数：不同动物的吼声
题目描述
在一个动物园里，有许多不同种类的动物，包括狮子、老虎和熊。每种动物都有一个名字，而且每种动物都有自己的叫声。你的任务是创建一个动物类（Animal）和三个派生类（Lion，Tiger，Bear），并实现一个虚函数 makeSound()，该函数会打印出动物的叫声。

要求：

Animal类应该有一个名为name的成员变量和一个名为makeSound的虚函数。
Lion，Tiger，Bear类应该从Animal类派生，并且应该重写makeSound函数。
Lion的makeSound函数应该打印"Roar"，Tiger的makeSound函数应该打印"Growl"，Bear的makeSound函数应该打印"Grr".
每个类应该有一个接受名字作为参数的构造函数，该构造函数应该设置name成员变量的值。
