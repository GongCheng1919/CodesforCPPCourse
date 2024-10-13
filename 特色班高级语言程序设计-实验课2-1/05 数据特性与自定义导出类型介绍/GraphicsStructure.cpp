#include <iostream>  
#include <cmath> // 用于 sqrt 和 pow 函数  
  
// 枚举类型，定义图形种类  
enum ShapeType {  
    Circle,  
    Rectangle,  
    Triangle  
};  
  
// 共用体，用于存储不同类型图形的数据  
union ShapeData {  
    struct {  
        double radius; // 圆形的半径  
    } circle;  
    struct {  
        double width, height; // 矩形的宽度和高度  
    } rectangle;  
    struct {  
        double base, height; // 三角形的底边和高  
    } triangle;  
};  
  
// 结构体，表示一个图形  
struct Shape {  
    ShapeType type;  
    ShapeData data;  
  
    // 计算面积的成员函数  
    double area() const {  
        switch (type) {  
            case Circle:  
                if (data.circle.radius < 0) return -1;  
                return M_PI * data.circle.radius * data.circle.radius;  
            case Rectangle:  
                if (data.rectangle.width < 0 || data.rectangle.height < 0) return -1;  
                return data.rectangle.width * data.rectangle.height;  
            case Triangle:  
                if (data.triangle.base < 0 || data.triangle.height < 0) return -1;  
                return 0.5 * data.triangle.base * data.triangle.height;  
            default:  
                return 0.0; // 默认情况处理  
        }  
    }  
};  
  
int main() {  
    double a, b, c, d, e;  
    std::cin >> a >> b >> c >> d >> e;  
    // 创建图形实例  
    Shape circle = {Circle, { .circle = {a} }};  
    Shape rectangle = {Rectangle, { .rectangle = {b, c} }};  
    Shape triangle = {Triangle, { .triangle = {d, e} }};  
  
    // 输出每个图形的面积  
    if (circle.area() == -1)  
        std::cout << "Circle area: error"  << std::endl;  
    else  
        std::cout << "Circle area: " << circle.area() << std::endl;  
  
    if (rectangle.area() == -1)  
        std::cout << "Rectangle area: error"  << std::endl;  
    else  
        std::cout << "Rectangle area: " << rectangle.area() << std::endl;  
  
  
    if (triangle.area() == -1)  
        std::cout << "Triangle area: error"  << std::endl;  
    else  
        std::cout << "Triangle area: " << triangle.area() << std::endl;  
  
    return 0;  
}
