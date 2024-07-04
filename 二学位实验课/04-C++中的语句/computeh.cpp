// 输入连续多个整数，并存储为一个整数数组 citations ，其中 citations[i] 表示研究者的第 i 篇论文被引用的次数。计算并返回该研究者的 h 指数。

// h指数的计算方式：h 代表“高引用次数” ，一名科研人员的 h 指数 是指他（她）至少发表了 h 篇论文，并且 至少 有 h 篇论文被引用次数大于等于 h 。如果 h 有多种可能的值，h 指数 是其中最大的那个。

// 输入：连续的n个整数，用空格隔开

// 输出：h指数值

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>

int calculateHIndex(const std::vector<int>& citations) {
    int n = citations.size();
    std::vector<int> sortedCitations = citations;
    std::sort(sortedCitations.begin(), sortedCitations.end(), std::greater<int>());

    int hIndex = 0;
    for (int i = 0; i < n; i++) {
        if (sortedCitations[i] >= i + 1) {
            hIndex = i + 1;
        } else {
            break;
        }
    }

    return hIndex;
}

int main() {
    std::vector<int> citations;
    std::string line;
    
    int n;
    std::vector<int> shape;
    std::getline(std::cin, line);  
    std::istringstream iss(line);  
    while(iss>>n){
        citations.push_back(n);
    }

    int hIndex = calculateHIndex(citations);
    std::cout << hIndex << std::endl;

    return 0;
}