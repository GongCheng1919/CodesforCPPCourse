#include <bits\stdc++.h>

using namespace std;

int main(){
    int n, i, k;
    cin >> n >> i >> k;

    switch(i){
        case 2:
            cout << n - floor(n * 0.01 * k) << endl;
            break;
        case 4:
            cout << k << endl;
            break;
        case 1:
            cout << n + k << endl;
        case 3:
            cout << n + floor(n * 0.01 * k) << endl;
            break;
    }
}
