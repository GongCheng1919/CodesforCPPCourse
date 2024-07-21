#include <cmath>
#include <iostream>
#include <string>

class Shape {
public:
    virtual double calculateArea() = 0;
    virtual double calculatePerimeter() = 0;
};

class Circle : public Shape {
public:
    double radius;
    Circle(double radius) : radius(radius) {}
    double calculateArea() override {
        return M_PI * radius * radius;
    }
    double calculatePerimeter() override {
        return 2 * M_PI * radius;
    }
};

class Rectangle : public Shape {
public:
    double width, height;
    Rectangle(double width, double height) : width(width), height(height) {}
    double calculateArea() override {
        return width * height;
    }
    double calculatePerimeter() override {
        return 2 * (width + height);
    }
};

class Triangle : public Shape {
public:
    double a, b, c;
    Triangle(double a, double b, double c) : a(a), b(b), c(c) {}
    double calculateArea() override {
        double s = (a + b + c) / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }
    double calculatePerimeter() override {
        return a + b + c;
    }
};

int main() {
    std::string name;
    std::cin >> name;
    
    Shape* ptr;
    if (name == "Circle") {
        double radius;
        std::cin>>radius;
        ptr = new Circle(radius);
    } else if (name == "Rectangle") {
        double width, height;
        std::cin>>width>>height;;
        ptr = new Rectangle(width, height);
    } else if (name == "Triangle") {
        double a, b, c;
        std::cin>>a>>b>>c;
        ptr = new Triangle(a, b, c);
    }else{
        return 0;
    }
    
    std::cout<<ptr->calculateArea()<<" "<< ptr->calculatePerimeter()<<std::endl;
    delete ptr;
    return 0;
}