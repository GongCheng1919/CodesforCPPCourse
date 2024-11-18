#include <iostream>
using namespace std;

struct element {
    string key;
    long long value;
};

// 重载 << 运算符
ostream& operator<<(ostream& os, const element& obj) {
    os << "[key: " << obj.key << ", value: " << obj.value << "]";
    return os;
}

int main() {
    string key;
    long long value;
    cin >> key >> value;
    element obj(key, value);
    cout << obj << endl; // 输出: {key: 42, value: 100}
    return 0;
}
