/*
请创建一个名为Point和一个名为Polar的类，分别用于表示笛卡尔坐标和极坐标下的点。
实现这两个类的加和减法,需要重载加法运算符+和减法运算符-，以便能够进行笛卡尔坐标和极坐标的加减运算。

输入： 输入包含三行，前两行每行包含两个浮点数, 一个字符p/q分别表示Point(p)和Polar(q)的坐标, 最后一行输入一个字符+/-表示运算符。输入错误的符号则输出error。

输出： 输出运算结果,运算结果应该为两行,第一行为笛卡尔坐标下的结果的两个坐标,第二行为极坐标下的运算结果的两个坐标。

注意:  对于极坐标,你总是需要将其坐标转换到笛卡尔坐标下进行计算，然后再转换回极坐标，来“加”这两个极坐标。
*/
#include <iostream>
#include <cmath>

class Polar;

class Point {
private:
    float x;
    float y;

public:
    Point(float x = 0, float y = 0) : x(x), y(y) {}

    Point(const Point& other) : x(other.x), y(other.y) {}
    
    Point(const Polar& other);

    float getX() const {
        return x;
    }
    float getY() const {
        return y;
    }

    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }

    Point operator+(const Polar& other) const;
    //  {
    //     Point otherPoint(other);
    //     return Point(x + otherPoint.x, y + otherPoint.y);
    // }

    Point operator-(const Point& other) const {
        return Point(x - other.x, y - other.y);
    }

    Point operator-(const Polar& other) const;
    // {
    //     Point otherPoint(other);
    //     return Point(x - otherPoint.x, y - otherPoint.y);
    // }

    operator Polar() const;
    //  {
    //     return Polar(*this);
    // }

    friend std::ostream& operator<<(std::ostream& os, const Point& point) {
        os << "(" << point.x << ", " << point.y << ")";
        return os;
    }
};

class Polar {
private:
    float r;
    float theta;

public:
    Polar(float r = 0, float theta = 0) : r(r), theta(theta) {}

    Polar(const Polar& other) : r(other.r), theta(other.theta) {}

    Polar(const Point& other) {
        r = sqrt(other.getX() * other.getX() + other.getY() * other.getY());
        theta = atan2(other.getY(), other.getX());
    }

    float getR() const {
        return r;
    }
    float getTheta() const {
        return theta;
    }

    Polar operator+(const Polar& other) const {
        return Point(*this) + Point(other);
    }

    Polar operator+(const Point& other) const {
        return Point(*this) + other;
    }

    Polar operator-(const Polar& other) const {
        return Point(*this) - Point(other);
    }

    Polar operator-(const Point& other) const {
        return Point(*this) - other;
    }

    operator Point() const {
        return Point(r * cos(theta), r * sin(theta));
    }

    friend std::ostream& operator<<(std::ostream& os, const Polar& polar) {
        os << "(" << polar.r << ", " << polar.theta << ")";
        return os;
    }
};

Point::Point(const Polar& other) {
    x = other.getR() * cos(other.getTheta());
    y = other.getR() * sin(other.getTheta());
}

Point Point::operator+(const Polar& other) const {
    Point otherPoint(other);
    return Point(x + otherPoint.x, y + otherPoint.y);
}

Point Point::operator-(const Polar& other) const {
    Point otherPoint(other);
    return Point(x - otherPoint.x, y - otherPoint.y);
}

Point::operator Polar() const {
    return Polar(*this);
}

int main() {
    float x1, y1, x2, y2;
    char type1, type2, op;
    std::cin >> x1 >> y1 >> type1;
    std::cin >> x2 >> y2 >> type2;
    std::cin >> op;

    Point p1, p2, result;
    if (type1 == 'p'){
        Point tmp(x1, y1);
        p1 = tmp;
    }
    else if (type1 == 'q'){
        Polar tmp(x1, y1);
        p1 = tmp;
    }else{
        std::cout << "error" << std::endl;
        return 0;
    }

    if (type2 == 'p'){
        Point tmp(x2, y2);
        p2 = tmp;
    }
    else if (type2 == 'q'){
        Polar tmp(x2, y2);
        p2 = tmp;
    }else{
        std::cout << "error" << std::endl;
        return 0;
    }
    // std::cout << p1 << std::endl;
    // std::cout << p2 << std::endl;

    if (op == '+') {
        result = p1 + p2;
    } else if (op == '-') {
        result = p1 - p2;
    }
    Polar polarResult = result;
    std::cout << result << std::endl;
    std::cout << polarResult << std::endl;

    return 0;
}