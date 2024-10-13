#include <bits\stdc++.h>

using namespace std;

int main(){
    int n, k;
    cin >> n >> k;

    for(int i = 0; i < k; i++){
        int index, para;
        cin >> index >> para;
        switch(index){
            case 2:
                n = n - floor(n * 0.01 * para);
                break;
            case 4:
                n = para;
                break;
            case 1:
                n = n + para;
                para = 50;
            case 3:
                n = n + floor(n * 0.01 * para);
                break;
        }
    }

    cout << n << endl;
}
