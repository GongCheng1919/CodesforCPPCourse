//方正类
/***********************************************************************************************

			定义一个二维方阵类，通过重载二元运算符“+、*”，求二维方阵的加法和乘法

************************************************************************************************/
#include<iostream>
using namespace std;
class square{
	
public:
	int a[4][4];
	square(){
	for (int i=0;i<4;i++)
			for (int j=0;j<4;j++)
				a[i][j] = 0;
	}
	square(int b[4][4]){
		for (int i=0;i<4;i++)
			for (int j=0;j<4;j++)
				a[i][j] = b[i][j];
	}
	/*void Input(int b[4][4]){
		for (int i=0;i<4;i++)
			for (int j=0;j<4;j++)
				a[i][j] = b[i][j];
	}*/
	square operator + (square obj){
		square Obj1;
		for (int i=0;i<4;i++)
			for (int j=0;j<4;j++)
				Obj1.a[i][j] = a[i][j] + obj.a[i][j];
		return Obj1;
	}
	square operator * (square obj){
		square Obj1;
		for (int i=0;i<4;i++)
			for (int j=0;j<4;j++)
			{
				int count = 0;
				for (int k = 0;k<4;k++){
					count += a[i][k] * obj.a[k][j] ;
				}
				Obj1.a[i][j] = count;
			}
		return Obj1;
	}
	void print(){
		for (int i=0;i<4;i++){
			for (int j=0;j<4;j++)
				cout<<a[i][j]<<"\t";
			cout<<endl;
		}
	}
};
int main(){
	//square obj1,obj2,obj3;
	int a[4][4],b[4][4];
	cout<<"请输入数组1："<<endl;
	for (int i=0;i<4;i++)
			for (int j=0;j<4;j++)
				a[i][j] = i+j;
	square x(a);
	x.print();
	cout<<"请输入数组2："<<endl;
	for (int i=0;i<4;i++)
			for (int j=0;j<4;j++)
				b[i][j] = i*j;
	square y(b);
	y.print();
	cout<<"(x+y)="<<endl;
	(x+y).print();
	cout<<"X*Y="<<endl;
	(x*y).print();
    return 0;
}



