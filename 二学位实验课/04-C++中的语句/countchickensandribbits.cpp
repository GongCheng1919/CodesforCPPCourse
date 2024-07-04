// "鸡兔同笼"是一个经典的数学问题，起源于中国的《算经》一书。问题的描述是这样的：一个笼子里面关着一些鸡和兔子（鸡有两只脚，兔子有四只脚）。如果我们数头有a个，数脚有b个，那么如何确定笼子里面有多少只鸡和多少只兔子？

// 输入：两个整数，分别表示头数和脚数

// 输出：鸡的个数和兔子的个数

#include <iostream>

int main(){
    int a, b;
    std::cin >> a >> b;

    float chickenCount = 0;
    float rabbitCount = 0;

    // Calculate the number of chickens and rabbits
    // based on the number of heads and legs
    // Each chicken has 2 legs and each rabbit has 4 legs
    // Let's assume all the animals are either chickens or rabbits

    // Calculate the maximum possible number of rabbits
    rabbitCount = float(b / 2) - a;

    // Calculate the maximum possible number of chickens
    chickenCount = a - rabbitCount;

    // Check if the calculated number of chickens and rabbits
    // satisfy the given number of heads and legs
    std::cout<< chickenCount <<" "<< rabbitCount<<std::endl;
    // std::cout << "Number of rabbits: " << rabbitCount << std::endl;
}