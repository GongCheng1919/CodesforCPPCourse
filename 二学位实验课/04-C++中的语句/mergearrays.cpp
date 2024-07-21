// 输入两个按 非递减顺序 排列的长度分别为m和n的整数数组 nums1 和 nums2。

// 请 合并 nums1 和  nums 两个数组为一个新的数组，并且使合并后的数组同样按 非递减顺序 排列。

// 输入：第一行分别输入m和n，

// 第二行输入m个整数

// 第三行输入n个整数

// 输出：输出合并后的数组

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int m, n;
    std::cin >> m >> n;

    std::vector<int> nums1(m);
    for (int i = 0; i < m; i++) {
        std::cin >> nums1[i];
    }

    std::vector<int> nums2(n);
    for (int i = 0; i < n; i++) {
        std::cin >> nums2[i];
    }

    std::vector<int> merged(m + n);
    std::merge(nums1.begin(), nums1.end(), nums2.begin(), nums2.end(), merged.begin());

    for (int i=0;i<m+n;i++) {
        std::cout << merged[i];
        if (i!= m+n-1) std::cout<<" ";
    }
    // std::cout << std::endl;

    return 0;
}
 