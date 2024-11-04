#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

int sum = 0;

int main() {
    int n;
    cin >> n;

    if (n == 1) {
        cout << 2;
        return 0;
    } else if (n == 2) {
        cout << 4;
        return 0;
    }

    int tmp = 0;
    vector<int> dp = vector<int>(n);
    dp[0] = 1;
    dp[1] = 1;
    dp[2] = 2;
    int sum = 4;

    for(int i = 3; ; i++){
        dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
        if (dp[i] > n){
            sum += n;
            break;
        } else {
            sum += dp[i];
        }
    }

    cout << sum;
}
