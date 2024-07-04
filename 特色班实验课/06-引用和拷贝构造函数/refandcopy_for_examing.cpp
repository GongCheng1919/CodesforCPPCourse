// 实现一个动态数组类，并实现一个函数用于排序并合并任何两个动态数组对象，要求该函数需要重载+并且可以连续调用
#include <iostream>
#include <string>
#include <sstream>

class DynamicArray {
private:
    int* arr;
    int size;
    float Scaling = 1.5;
    int capacity = 10;
    int id;
    static int array_id;

public:
    DynamicArray() {
        capacity = 0;
        arr = nullptr;
        id = array_id;
        array_id++;
        std::cout << "Construct: " << this->id << std::endl;
        // Your code Here

    }

    DynamicArray(int* array, int arraySize) {
        std::cout << "Construct: " << this->id << std::endl;
         // Your code Here

    }

    DynamicArray(const DynamicArray& other) {
        std::cout << "Copy Construct: " << this->id <<" From: "<< other.id << std::endl;
        // Your code Here

    }

    ~DynamicArray() {
        std::cout << "Destruct: "  << this->id<< std::endl;
        delete[] arr;
    }

    int operator[](int index) const {
        // Your code Here

    }

    void push_back(int value) {
        if (size == capacity) {
            if (capacity == 0) 
                capacity = 10;
            else
                capacity = capacity * Scaling;
            // Your code Here


            std::cout << "Increase "<<this->id<<"'s capacity to "<< capacity << std::endl;
        }
        (*this)[size++] = value;
    }


    DynamicArray& operator=(const DynamicArray& other) {
        std::cout << "Assignment Construct: " << this->id << std::endl;
        // Your code Here
        
        return *this;
    }

    DynamicArray operator+(const DynamicArray other) {
        // Your code Here
        
    }

    friend DynamicArray operator||(DynamicArray src, DynamicArray dst) {
        // Sort:  Your code Here
        
        // Merge: Your code Here
        
    }

    void print() const {
        for (int i = 0; i < size; i++) {
            std::cout << (*this)[i];
            if (i != size - 1) {
                std::cout << " ";
            } else {
                std::cout << std::endl;
            }
        }
    }
};

int DynamicArray::array_id = 0;

class Circle {
public:
    Circle() {}

    // 类型转换运算符
    operator Point() const {
        return Point(*this);
    }
};

class Point {
public:
    Point() {}
    // 构造函数
    Point(const Circle& circle) {
        // 从 Circle 对象初始化 Point 对象
    }
};
Circle circle;
Point point = circle;  // 调用 Circle::operator Point() const
Circle circle;
Point point = Point(circle);  // 调用 Point::Point(const Circle& circle)

int main() {
    int n;
    std::cin>>n;
    std::cin.ignore();
    std::string line;
    int num;
    // Init DynamicArray
    DynamicArray* arrays = new DynamicArray[n];
    for(int i = 0; i < n; i++){
        std::getline(std::cin, line);
        std::istringstream stream(line);
        while (stream >> num) {
            std::cout << num << std::endl;
            arrays[i].push_back(num);
        }
    }
    // Test +
    DynamicArray* array1 = new DynamicArray();
    for (int i = 0; i < n; i++) {
        *array1 = *array1 + arrays[i];
    }
    array1->print();
    delete array1;

    // Test ||
    DynamicArray array2 = arrays[0];
    for (int i = 1; i < n; i++) {
        array2 = array2 || arrays[i];
    }
    array2.print();

    // Release
    delete[] arrays;

    return 0;
}