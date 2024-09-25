#include "extern_demo.h"

int t=2;
int main(){
    t=5;
    fa(t+1);
    cout << t <<endl;
}
void fa(int s){
    cout << s + fb() <<endl;    
}
