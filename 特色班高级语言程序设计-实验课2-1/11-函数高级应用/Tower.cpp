#include <iostream>
using namespace std;

long long cnt = 0;

void Towers(int n,char a,char b,char c){
    if(n==1){
        cnt++;
    }
    else{
        Towers(n-1,a,c,b);
        cnt++;
        Towers(n-1,b,a,c);
    }
}

int main(int argc, char *argv[]) {
    int n;
    cin>>n;
    if (n == 0) {
        cout << 0;
        return 0;
    }
    Towers(n,'A','B','C');
    cout << cnt;
}
