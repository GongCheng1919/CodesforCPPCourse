#include <bits\stdc++.h>

using namespace std;

int main(){
    int m[4],n[8];
    cin >> m[0] >> m[1] >> m[2] >> m[3];
    cin >> n[0] >> n[1] >> n[2] >> n[3] >> n[4] >> n[5] >> n[6] >> n[7];

    int i;
    int sum = 0;
    for(i = 0; i < 4; i++) {
        sum += m[i];
    }
    cout << sum << " " << i << endl ;
    sum = 0;
    for(int i = 0; i < 8; i++) {
        sum += n[i];
    }
    cout << sum << " " << i << endl;
}
