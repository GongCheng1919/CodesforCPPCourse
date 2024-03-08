#include <iostream>
#include <bitset>

std::string intToBinary(int num) {
    std::bitset<32> binary(num);
    return binary.to_string();
}

std::string floatToBinary(float num) {
    union {
        float input;
        int output;
    } data;
    data.input = num;
    std::bitset<32> binary(data.output);
    return binary.to_string();
}

int main() {
    int a;
    float b;
    std::cin>>a>>b;
    std::cout << intToBinary(a) << std::endl;
    std::cout << floatToBinary(b) << std::endl;
    return 0;
}