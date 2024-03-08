#include <iostream>
#include <cstring>

int sumIntAndFloat(int a, float b) {
    return a + static_cast<int>(b);
}

int sumAsciiCodes(const char* str) {
    int len = strlen(str);
    return static_cast<int>(str[0]) + static_cast<int>(str[len - 1]);
}

int sumArrayElements(int* arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += *(arr + i);
    }
    return sum;
}

int main() {
    std::string str;
    std::cin>>str;
    std::cout << sumIntAndFloat(5, 3.7) << std::endl;
    std::cout << sumAsciiCodes(str.c_str()) << std::endl;
    int arr[] = {1, 2, 3, 4, 5};
    std::cout << sumArrayElements(arr, 5) << std::endl;
    return 0;
}