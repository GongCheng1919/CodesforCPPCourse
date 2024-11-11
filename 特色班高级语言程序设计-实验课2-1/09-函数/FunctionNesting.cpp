#include <iostream>
#include <iomanip>

int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

int permutation(int n, int k) {
    return factorial(n) / factorial(n - k);
}

int combination(int n, int k) {
    int a = factorial(n), b = factorial(k), c = factorial(n - k);

    return a / (b * c);
}

int main(){
    int m, n, a;
    std::cin >> m >> n >> a;

    double total = combination(m, a) * combination(n, m - a);
    std::cout << total << " " << std::setprecision(4) << total / combination(m + n, a) << std::endl;

}
