// 输入一个字符串，根据字符出现的 频率 对其进行 降序排序 。一个字符出现的 频率 是它出现在字符串中的次数。如果两个字符的频率相同，则按照其字母表顺序排序。

// 输入：一个字符串。

// 输出：排序后的字符串。
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <vector>

bool compare(std::pair<char, int> a, std::pair<char, int> b) {
    if (a.second == b.second) {
        return a.first < b.first;
    }
    return a.second > b.second;
}

std::string sortStringByFrequency(const std::string& str) {
    std::unordered_map<char, int> frequencyMap;
    std::vector<std::pair<char,int>> frequencyPairs;
    for (char c : str) {
        frequencyMap[c]++;
    }

    for (auto it = frequencyMap.begin(); it != frequencyMap.end(); ++it) {
        frequencyPairs.push_back(*it);
    }

    std::sort(frequencyPairs.begin(), frequencyPairs.end(), compare);

    std::string sortedStr;
    for (auto pair : frequencyPairs) {
        sortedStr += std::string(pair.second, pair.first);
    }

    return sortedStr;
}

int main() {
    std::string input;
    // std::cout << "Enter a string: ";
    // std::cin.getline(input);
    std::getline(std::cin,input);

    std::string sortedString = sortStringByFrequency(input);
    std::cout << sortedString << std::endl;

    return 0;
}