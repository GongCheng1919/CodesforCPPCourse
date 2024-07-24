#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
// 点类
class Point {

    // 二维点
  private:
    struct Spoint
    // 单个点的结构体
    {
        float m_x;
        float m_y;

        // 重载点的运算操作符
        Spoint operator+(const Spoint &other) {
            return {m_x + other.m_x, m_y + other.m_y};
        }
        Spoint operator-(const Spoint &other) {
            return {m_x - other.m_x, m_y - other.m_y};
        }

        // 结构体内声明友元函数
        friend void distance(const Point &point1, const Point &point2);
    };
    Spoint spoint;

  public:
    // 创建点
    void CreateSinglePoint() {
        cin >> spoint.m_x >> spoint.m_y;
    }

    // 计算两点之间的距离
    void Display() {
        cout << "(" << spoint.m_x << ", " << spoint.m_y << ")" << '\n';
    }

  public:
    // 类内声明友元函数
    friend void distance(const Point &point1, const Point &point2);
};
void distance(const Point &point1, const Point &point2) {
    float disx = point1.spoint.m_x - point2.spoint.m_x;
    float disy = point1.spoint.m_y - point2.spoint.m_y;

    printf("%.2f\n", sqrt(disx * disx + disy * disy));
}

int main() {
    Point p1, p2;
    p1.CreateSinglePoint();
    p2.CreateSinglePoint();
    p1.Display();
    p2.Display();
    distance(p1, p2);

    return 0;
}