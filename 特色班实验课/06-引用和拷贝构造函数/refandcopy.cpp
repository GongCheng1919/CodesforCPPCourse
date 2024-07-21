// 实现一个动态数组类，并实现一个函数用于排序并合并任何两个动态数组对象，要求该函数需要重载+并且可以连续调用

#include <iostream>
#include <algorithm>
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
    DynamicArray() : arr(nullptr), size(0) {
        capacity = 0;
        arr = nullptr;
        id = array_id;
        array_id++;
        std::cout << "Construct: " << this->id << std::endl;
    }

    DynamicArray(int* array, int arraySize) : size(arraySize) {
        id = array_id;
        array_id++;
        std::cout << "Construct: " << this->id << std::endl;
        while (size > capacity) {
            capacity = capacity * Scaling;
        }
        arr = new int[capacity];
        for (int i = 0; i < size; i++) {
            arr[i] = array[i];
        }
    }

    DynamicArray(const DynamicArray& other) : size(other.size) {
        id = array_id;
        array_id++;
        std::cout << "Copy Construct: " << this->id <<" From: "<< other.id << std::endl;
        arr = new int[size];
        size = other.size;
        capacity = other.capacity;
        for (int i = 0; i < size; i++) {
            arr[i] = other.arr[i];
        }
    }

    ~DynamicArray() {
        std::cout << "Destruct: "  << this->id<< std::endl;
        if (arr != nullptr)
            delete[] arr;
    }

    void push_back(int value) {
        if (size == capacity) {
            if (capacity == 0) 
                capacity = 10;
            else
                capacity *= Scaling;
            std::cout << "Increase "<<this->id<<"'s capacity to "<< capacity << std::endl;
            int* newArr = new int[capacity];
            for (int i = 0; i < size; i++) {
                newArr[i] = arr[i];
            }
            if (arr != nullptr)
                delete[] arr;
            arr = newArr;
        }
        // arr[size++] = value;
        (*this)[size++] = value;
    }

    int& operator[](int index) const {
        if (index < 0 || index >= size) {
             throw std::out_of_range("Index out of range");
        }
        return arr[index];
    }

    DynamicArray& operator=(const DynamicArray& other) {
        std::cout << "Assignment Construct: " << this->id << std::endl;
        
        if (this != &other) {
            delete[] arr;
            size = other.size;
            capacity = other.capacity;
            arr = new int[capacity];
            for (int i = 0; i < size; i++) {
                (*this)[i] = other.arr[i];
            }
        }
        return *this;
    }

    DynamicArray& operator+(const DynamicArray& other) {
        int newSize = size + other.size;
        for (int i = 0; i < other.size; i++) {
            this->push_back(other.arr[i]);
        }
        return *this;
    }

    friend DynamicArray& operator||(DynamicArray& src, DynamicArray& dst) {
        // Sort
        std::sort(src.arr, src.arr + src.size);
        std::sort(dst.arr, dst.arr + dst.size);
        // Merge
        int newSize = src.size + dst.size;
        int* dstArr = dst.arr;
        int dst_size = dst.size;
        dst.arr = new int[dst.capacity];
        dst.size = 0;
        int i = 0, j = 0, k = 0;
        while (i < dst_size || j < src.size) {
            if (j>=src.size) {
                dst.push_back(dstArr[i++]);
                continue;
            }
            if (i>=dst_size) {
                dst.push_back(src.arr[j++]);
                continue;
            }
            if (dstArr[i] < src.arr[j]) {
                dst.push_back(dstArr[i++]);
            }else{
                dst.push_back(src.arr[j++]);
            }
        }
        delete[] dstArr;
        return dst;
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