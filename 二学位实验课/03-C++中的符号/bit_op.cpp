#include <iostream>

int bitop(int num1, int num2, char op, int start_bit, int end_bit) {
    // 创建一个掩码，用于选择需要参与运算的位
    int mask = ((1 << (end_bit - start_bit)) - 1) << start_bit;
    // std::cout << mask << std::endl;
    
    // 根据操作符进行位运算
    switch (op) {
        case '&':
            return (num1 & num2) & mask;
        case '|':
            return (num1 | num2) & mask;
        case '^':
            return (num1 ^ num2) & mask;
        case '~':
            return ~num1 & mask;
        case '>':
            return (num1 >> num2) & mask;
        case '<':
            return (num1 << num2) & mask;
        default:
            std::cout << "error" << std::endl;
            return -1;
    }
}

int main() {
    int num1 = 33;  // 二进制表示为00100001
    int num2 = 10;  // 二进制表示为00001010
    char op = '&';
    int start_bit = 0;
    int end_bit = 3;
    
    std::cin>>num1>>num2>>op>>start_bit>>end_bit;

    int result = bitop(num1, num2, op, start_bit, end_bit);
    if (result != -1)
        std::cout << result << std::endl;
    
    return 0;
}