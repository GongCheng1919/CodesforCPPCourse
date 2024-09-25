#include <iostream>
using namespace std;

void func(){
    cout<<"hello world!"<<endl;
}

class graphelem
{ // 自定义类 graphelem，将作为其他图元类的基类
protected:
    int color; // 颜色 color
public:
    graphelem()
    {
        color = 0;
    }
    void draw()
    {
        cout << "draw graphelem" << endl;
    }; // 基类中含有一个虚函数
};

class line : public graphelem
{ // 自定义类 line，为基类 graphelem 的派生类 
    public: // 虚函数 draw 负责画出“line”
    void draw() { cout << "draw line" << endl; }; 
};
class circle : public graphelem
{ // 自定义类 circle，为基类 graphelem 的派生类
    public: // 虚函数 draw，负责画出“circle” 
    void draw(){ cout << "draw circle" << endl; }; 
};
class triangle : public graphelem
{ // 类 triangle，为基类 graphelem 的派生类
    public: // 虚函数 draw 负责画出“triangle”
    void draw(){ cout << "draw triangle" << endl; }; 
};

class triangle2 : public triangle
{ // 类 triangle，为基类 graphelem 的派生类
    public: // 虚函数 draw 负责画出“triangle”
    void draw(){ cout << "draw triangle2" << endl; }; 
};

int main()
{
    // line ln1; circle cir1; triangle tri1;
    // ln1.draw(); cir1.draw(); tri1.draw();
    graphelem *p[4]; // 定义一个指针数组，数组元素为基类 graphelem 的指针
    p[0] = new line(); // 指针数组的第一个元素指向派生类 line 的对象
    p[1] = new circle(); // 指针数组的第二个元素指向派生类 circle 的对象
    p[2] = new triangle(); // 指针数组的第三个元素指向派生类 triangle 的对象
    p[3] = new triangle2(); // 指针数组的第三个元素指向派生类 triangle 的对象
    printf("address of func is %p\n",&func);
    for (int i = 0; i < 4; i++){
        p[i]->draw(); // 调用指针数组中各个元素的 draw() 函数
        printf("%p, %p",p[i],&(p[i]->draw));
        printf(", p[%d]->graphelem::draw地址:%p", i, &(p[i]->graphelem::draw));
        printf(", p[%d]->draw地址:%p\n", i, &(p[i]->draw));
    }
    // ((triangle*)p[3])->triangle::draw();
    return 0;
}


