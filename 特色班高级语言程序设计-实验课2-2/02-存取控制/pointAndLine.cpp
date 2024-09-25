/*
输入描述：
键盘输入4个整数，分别是直线的斜率slope和截距bias，以及点的 x 坐标和 y 坐标

输出描述：
圆类中实现 isPointerOfLine方法，在该方法中输出点和圆的关系，

如果点在直线的上方，则输出“upper”；

如果点是直线中的一个点，则输出“of”；

如果点在直线的下方，则输出“lower”。
*/
#include <iostream>
#include <vector>

using namespace std;

namespace Gemotry {

// 因为你Point的友元函数之前还没有定义Line 所以参数那里不识别 前置声明一下就好了
// 前置声明,用来处理在友元函数中调用多个类但是出现类的定义有先后
// 从而导致无法访问的问题，前置声明能够保证友元函数对于所有类的调用都能够识别
class Point;
class Line;

// 点类
class Point {

  private:
    // 二维点
    struct Spoint {
        int m_x;
        int m_y;

        // friend void isPointOfLine(const Point& point, const Line& line);

        // 重载点的加减即可
        Spoint operator+(const Spoint &other) {
            return {m_x + other.m_x, m_y + other.m_y};
        }
        Spoint operator-(const Spoint &other) {
            return {m_x - other.m_x, m_y - other.m_y};
        }
    };
    Spoint spoint;

    friend void isPointOfLine(const Point &point, const Line &line);

  public:
    void CreateSinglePoint() {
        cin >> spoint.m_x >> spoint.m_y;
    }

  public:
};

// 直线类
class Line {

  private:
    // 二维直线由斜率和直线与y轴截距确定
    struct Sline {
        // 斜率
        int slope;

        // y轴截距
        int bias;
    };

    Sline sline;

  public:
    void CreatSingleLine() {
        cin >> sline.slope >> sline.bias;
    }

  public:
    friend void isPointOfLine(const Point &point, const Line &line);
};

// 用y-(kx+b)和0的关系来判断点和直线的位置关系
void isPointOfLine(const Point &point, const Line &line) {
    int position(point.spoint.m_y - (line.sline.slope * point.spoint.m_x + line.sline.bias));

    if (0 == position)
        cout << "of";
    else if (position > 0)
        cout << "upper";
    else
        cout << "lower";
}
}; // namespace Gemotry

using namespace Gemotry;

int main() {
    Point mypoint;
    Line myline;
    myline.CreatSingleLine();
    mypoint.CreateSinglePoint();

    isPointOfLine(mypoint, myline);

    return 0;
}