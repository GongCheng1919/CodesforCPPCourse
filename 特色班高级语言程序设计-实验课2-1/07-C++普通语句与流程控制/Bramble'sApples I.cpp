#include <bits\stdc++.h>

using namespace std;

int main(){
    int n, m, x, y;
    cin >> n >> m >> x >> y;
    cout << n + m << endl;
    cout << ((n + m - x > 0) ? (n + m - x) : 0) << endl;
    cout << ((n + m - x - y > 0) ? (n + m - x - y) : 0) << endl;
}
