#include <bits\stdc++.h>

using namespace std;

int main(){
    int n;
    cin >> n;

    if (n > 0)
        cout << log(n) << endl;
    else
        cout << "error" << endl;

    n = pow(n, 3);

    if (n > 0)
        cout << log(n) << endl;
    else
        cout << "error" << endl;

    n = pow(n, 2);

    if (n > 0)
        cout << log(n) << endl;
    else
        cout << "error" << endl;
}
