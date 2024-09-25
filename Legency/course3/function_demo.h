//function_demo.h
#include<iostream>
#include<math.h>
using namespace std;

//compute cuberoot of x
float cuberoot (float x)
{
    float root, croot;
    const float eps=1e-6;
    croot=x;
    do{ 
        root=croot;
        croot=(2* root+x/(root* root))/3;
    }while(fabs(croot-root)>eps);
    return croot;
}

//Compute the result of x where x^3+px+q=0
float cardan_v2(float p,float q){
    float xr, a=a=sqrt(q/2* q/2+p/3* p/3* p/3);
    xr=cuberoot(-q/2+a)+cuberoot(-q/2-a);
    cout<<endl<<"CardanV2: The real root of the equation is "<<xr;
    return xr;
}

//Compute the result of x where x^3+px+q=0
float cardan(float p,float q){
    float xr,root;
    const float eps=1e-6; 
    // Compute sqrt of a=q/2* q/2+p/3* p/3* p/3
    float a=sqrt(q/2* q/2+p/3* p/3* p/3);
    // Compute cuberoot of -q/2+a
    float croot = -q/2+a,x=croot;
    do {
        root=croot;
        croot=(2* root+x/(root* root))/3;
    } while(fabs(croot-root)>eps);
    xr=croot;
    // Compute cuberoot of -q/2-a
    croot= -q/2-a; x=croot;
    do {
        root=croot;
        croot=(2* root+x/(root* root))/3;
    } while (fabs(croot-root)>eps);
    xr+=croot;
    cout<<endl<<"Cardan: The real root of the equation is "<<xr;
    return xr;
}

int& add(int& a, int b){
    return a+=b;
}

void f1 (int,int);
void f2 (int);

void f1 (int x, int y) {
    int m = 2;
    x *= m ;
    y++;
    f2 ((x+y)/m);
}
void f2 (int p) {
    if (p <= 100) cout << p;
}

void inv(int n)
{
    int i; 
    cin>>i;
    if (n>1) 
        inv(n-1); 
    else 
        cout<<"---- The result ----"<<endl;
    cout<< i <<" ";
}

void conv(int n){
    if (n<10) { 
        cout << n; 
        return; 
    }
    cout << n%10;
    conv(n/10);
 }
