#include <iostream>

inline char compare(int a, int b){
    return a > b ? '>' : '<';
}

int main() {
    int m;
    std::cin >> m;
    while(m--){
        int x, y;
        std::cin >> x >> y;
        std::cout << compare(x, y) << std::endl;
    }
}
