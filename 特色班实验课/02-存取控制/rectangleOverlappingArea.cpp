/*
给你二维平面上两个由直线构成且边与坐标轴平行/垂直的矩形，请你计算并返回两个矩形重叠部分的面积。

每个矩形由其 左下 顶点和 右上 顶点坐标表示：

第一个矩形由其左下顶点 (ax1, ay1) 和右上顶点 (ax2, ay2) 定义。 第二个矩形由其左下顶点 (bx1, by1) 和右上顶点 (bx2, by2)
定义。

要求：

（1）矩形用类Rectangle表示

（2）声明友元函数friend int getArea(Rectangle m1,Rectangle m2) 来计算面积
*/
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

namespace Gemotry {
class Rectangle;
// 二维点
struct Point {
    int m_x;
    int m_y;

    void CreatePoint() {
        cin >> m_x >> m_y;
    }
};
// 矩形类
class Rectangle {
  public:
    // 矩形由左下和右上两个点确定
    Point leftDown;
    Point rightUp;

  public:
    void CreateSrectangle() {
        leftDown.CreatePoint();
        rightUp.CreatePoint();
    }

    // 计算两个矩形重叠面积,简单的用整数类型实现
    int OverLappingAreaOfTwoRectangle(const Rectangle &other);
};
int Rectangle::OverLappingAreaOfTwoRectangle(const Rectangle &other) {
    // 计算两个矩形的重叠部分长和宽即可
    int width = min(this->rightUp.m_x, other.rightUp.m_x) - max(this->leftDown.m_x, other.leftDown.m_x);
    int height = min(this->rightUp.m_y, other.rightUp.m_y) - max(this->leftDown.m_y, other.leftDown.m_y);

    int s = width * height;
    return s;
}
}; // namespace Gemotry

using namespace Gemotry;

int main() {
    Rectangle rectA, rectB;
    rectA.CreateSrectangle();
    rectB.CreateSrectangle();

    cout << rectA.OverLappingAreaOfTwoRectangle(rectB);

    return 0;
}
