#include <iostream>
using namespace std;

// 函数声明，重新排列数组中的元素
int rearrangeArray(int* arr, int n) {
    int* left = arr;           // 指向数组的起始位置
    int* right = arr + n - 1;  // 指向数组的末尾位置

    // 双指针法重新排列数组
    while (left < right) {
        // 向右移动左指针，直到找到一个奇数
        while (left < right && *left % 2 == 0) {
            ++left;
        }
        // 向左移动右指针，直到找到一个偶数
        while (left < right && *right % 2 != 0) {
            --right;
        }
        // 交换奇数和偶数的位置
        if (left < right) {
            int temp = *left;
            *left = *right;
            *right = temp;
        }
    }
    return left - arr;
}
void sort(int* p, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[i] > p[j])
            {
                int temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}
int main() {
    int n;
    cin >> n;
    int* arr = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    // 调用函数重新排列数组
    int x=rearrangeArray(arr, n);
    // 输出重新排列后的数组
    sort(arr, x);
    sort(arr + x, n - x);
    for (int* ptr = arr; ptr < arr + n; ++ptr) {
        cout << *ptr << " ";
    }
    return 0;
}
