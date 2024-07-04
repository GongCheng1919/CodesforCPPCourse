// 连续输入多个无序整数以空格隔开，并存储为一个数组 nums，返回数组在排序之后，相邻元素之间最大的差值 。

// 输入：连续多个整数并以空格隔开。

// 输出：排序后数组相邻元素的最大差值。
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

int main() {
    std::vector<int> nums;
    std::string line;
    
    int n;
    std::vector<int> shape;
    std::getline(std::cin, line);  
    std::istringstream iss(line);  
    while(iss>>n){
        nums.push_back(n);
    }
    
    // Sort the nums vector
    std::sort(nums.begin(), nums.end());
    
    // Calculate the maximum difference between adjacent elements
    int maxDiff = 0;
    for (int i = 1; i < nums.size(); i++) {
        int diff = nums[i] - nums[i-1];
        if (diff > maxDiff) {
            maxDiff = diff;
        }
    }
    
    // Print the maximum difference
    std::cout << maxDiff << std::endl;
    
    return 0;
}