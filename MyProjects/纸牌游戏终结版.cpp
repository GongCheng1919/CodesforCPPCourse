/**************************************************************************
                             1210517
							 大作业P89 自立题二十
**************************************************************************/
#include<iostream>
#include<stdlib.h>
#include <stdio.h>
#include<string.h>
#include<time.h>
#include<iomanip>
using namespace std;
bool check(int a[])
{
	int i,j;
	for (i=0;i<9;i++)
	{
		for (j=i+1;j<9;j++)
			if (a[i]==a[j])
				return true;
	}
	return false;
}
bool check1(int a[])
{
	int i,j;
	for (i=0;i<3;i++)
	{
		for (j=i+1;j<3;j++)
			if (a[i]==a[j])
				return true;
	}
	return false;
}
bool check(int a[],int b[])
{
	int i,j;
	for (i=0;i<9;i++)
	{
		for (j=0;j<9;j++)
			if (a[i]==b[j])
				return true;
	}
	return false;
}
bool check1(int a[],int b[])
{
	int i,j;
	for (i=0;i<3;i++)
	{
		for (j=0;j<3;j++)
			if (a[i]==b[j])
				return true;
	}
	return false;
}
int main()
{
	char n;
	do{
	int i,j,r,a[3][9],b[3][3];
	int line1,line2,line3;
	char card[54][6],shu[13]={'A','2','3','4','5','6','7','8','9',' ','J','Q','K'},hua[4]={35,36,37,38};//hua[4]={3,6,5,4};
	for (r=0;r<4;r++)
	{
		for (i=0;i<13;i++)
		{
			card[(13*r)+i][0]=hua[r];
			//cout<<hua[r]<<endl;
			card[13*r+i][1]='-';
			card[13*r+i][2]=shu[i];
			card[13*r+i][3]='\0';
		}
		card[13*r+9][2]='1';
		card[13*r+9][3]='0';
		card[13*r+9][4]='\0';
	}
	card[52][0]='K';card[52][1]='I';card[52][2]='N';card[52][3]='G';card[52][4]='1';card[52][5]='\0';
	card[53][0]='K';card[53][1]='I';card[53][2]='N';card[53][3]='G';card[53][4]='2';card[53][5]='\0';
	/*for (i=0;i<54;i++)
		cout<<card[i]<<endl;*/
	cout<<"--------------------------------------------------------------------------------"<<endl;
	srand((unsigned)time(NULL));
	cout.width(6);
	cout<<"line1:";
	do{
		for (i=0;i<9;i++)
		    a[0][i]=rand()%54;
	}while(check(a[0]));
	for (i=0;i<9;i++) cout<<setw(6)<<card[a[0][i]];
	cout<<endl;
	cout.width(6);
	cout<<"line2:";
	do{
		for (i=0;i<9;i++)
		    a[1][i]=rand()%54;
	}while(check(a[1])||check(a[1],a[0]));
	for (i=0;i<9;i++) cout<<setw(6)<<card[a[1][i]];
	cout<<endl;
	cout.width(6);
	cout<<"line3:";
	do{
		for (i=0;i<9;i++)
		    a[2][i]=rand()%54;
	}while(check(a[2])||check(a[2],a[0])||check(a[2],a[1]));
	for (i=0;i<9;i++) cout<<setw(6)<<card[a[2][i]];
	cout<<endl;
	cout<<"--------------------------------------------------------------------------------"<<endl;
	cout<<"Remember a card,and tell me what line it reside in(1/2/3):";
	r=1;
	while (r)//判断是否输入错误
	{
		cin>>line1;
		if (line1<1||line1>3) cout<<"输入错误!请重新输入输入1或2或3行（line）：";
		else r=0;
	}
	line1=line1-1;//换算成C++数组下标
	cout<<"--------------------------------------------------------------------------------"<<endl;
	int T[18];//建一个集合
	if (line1==0){
		for (j=0;j<9;j++) T[j]=a[1][j];
		for (j=0;j<9;j++) T[9+j]=a[2][j];
	}
	if (line1==1){
		for (j=0;j<9;j++) T[j]=a[0][j];
		for (j=0;j<9;j++) T[9+j]=a[2][j];
	}
	if (line1==2){
		for (i=0;i<2;i++)
			for (j=0;j<9;j++) T[i*9+j]=a[i][j];
	}
	cout.width(6);
	cout<<"line1:";
	do{
		for (i=0;i<3;i++) b[0][i]=rand()%9;//注意a[i][j]与b[i][j]的关系
	}while (check1(b[0]));
	for (i=0;i<3;i++) cout<<setw(6)<<card[a[line1][b[0][i]]];//注意a[i][j]与b[i][j]的关系
	for (i=0;i<18;i=i+3) cout<<setw(6)<<card[T[i]];
	cout<<endl;
	cout.width(6);
	cout<<"line2:";
	do{
		for (i=0;i<3;i++) b[1][i]=rand()%9;
	}while (check1(b[1])||check1(b[1],b[0]));
	for (i=0;i<3;i++) cout<<setw(6)<<card[a[line1][b[1][i]]];
	for (i=1;i<18;i=i+3) cout<<setw(6)<<card[T[i]];
	cout<<endl;
	cout.width(6);
	cout<<"line3:";
	do{
		for (i=0;i<3;i++) b[2][i]=rand()%9;
	}while (check1(b[2])||check1(b[2],b[0])||check1(b[2],b[1]));
	for (i=0;i<3;i++) cout<<setw(6)<<card[a[line1][b[2][i]]];
	for (i=2;i<18;i=i+3) cout<<setw(6)<<card[T[i]];
	cout<<endl;
	cout<<"--------------------------------------------------------------------------------"<<endl;
	cout<<"Remember a card,and tell me what line it reside in(1/2/3):";
	r=1;//初始化r
	while (r)//判断是否输入错误
	{
		cin>>line2;
		if (line2<1||line2>3) cout<<"输入错误!请重新输入输入1或2或3行(line)：";
		else r=0;
	}
	line2=line2-1;//换算成C++数组下标
	cout<<"--------------------------------------------------------------------------------"<<endl;
	int U[24];//存入未选上的牌
	if (line2==0){
		for (i=0;i<18;i++) U[i]=T[i];
		for (i=0;i<3;i++) U[18+i]=a[line1][b[1][i]];
		for (i=0;i<3;i++) U[21+i]=a[line1][b[2][i]];
	}
	if (line2==1){
		for (i=0;i<18;i++) U[i]=T[i];
		for (i=0;i<3;i++) U[18+i]=a[line1][b[0][i]];
		for (i=0;i<3;i++) U[21+i]=a[line1][b[2][i]];
	}
	if (line2==2){
		for (i=0;i<18;i++) U[i]=T[i];
		for (i=0;i<3;i++) U[18+i]=a[line1][b[0][i]];
		for (i=0;i<3;i++) U[21+i]=a[line1][b[1][i]];
	}
	for (r=0;r<=2;r++)//输出最后三行
	{
		cout<<"line"<<(r+1)<<":";
		cout.width(6);
		for (i=0+r;i<12;i=i+3) cout<<setw(6)<<card[U[i]];
		cout<<setw(6)<<card[a[line1][b[line2][r]]];
		for (i=12+r;i<24;i=i+3) cout<<setw(6)<<card[U[i]];
		cout<<endl;
	}
	cout<<"--------------------------------------------------------------------------------"<<endl;
	cout<<"Remember a card,and tell me what line it reside in(1/2/3):";
	while (r)//判断是否输入错误
	{
		cin>>line3;
		if (line3<1||line3>3) cout<<"输入错误!请重新输入输入1或2或3行（line）：";
		else r=0;
	}
	line3=line3-1;//换算成C++数组下标
	cout<<"what you guess card is=>"<<card[a[line1][b[line2][line3]]]<<endl;
	r=1;
	cout<<"您想再玩一次吗？（y/n）:";
	while (r)//判断是否输入错误
	{
		cin>>n;
		if (n=='y'||n=='n') r=0;
		else cout<<"输入错误，请重新输入（y/n）：";
	}
	}while(n=='y');
	cout<<"*********************************谢谢使用***************************************"<<endl;
	system("pause");
	return 0;
}