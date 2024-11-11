#include <iostream>

int m, n;

void solve() {
    if (m >= n){
        std::cout << "Hic!~";
    } else {
       std::cout << "Briar, I'm hungry!";
    }
}

int main(){
    std::cin >> m >> n;
    solve();
    return 0;
}
