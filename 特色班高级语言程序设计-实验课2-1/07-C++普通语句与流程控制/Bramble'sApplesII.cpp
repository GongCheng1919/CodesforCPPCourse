#include <bits\stdc++.h>

using namespace std;

int main(){
    int n, m, x, y, z;
    cin >> n >> m >> x >> y >> z;

    int temp = n + m;
    cout << temp << endl;

    if (x > temp / 2)
        temp -= temp / 2;
    else
        temp -= x;
    cout << temp << endl;

    if (y < temp) {
        temp -= y;
        cout << temp << endl;
    } else {
        temp = 0;
        cout << temp << endl << z << endl;
    }
}
