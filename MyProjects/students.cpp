//The First Work
/************************************************************************************
			设计学生类(Student)，数据成员是学号、姓名与成绩(数学、外语与计算机)，
		对类对象数组进行输入；设计以学号为参数的搜索函数，从数组中搜索并返回
		学生信息
*************************************************************************************/
#include<iostream>
#include<string.h>
using namespace std;
class student{
private:
	char *ID;//学号
	char *Name;//姓名
	int Math;//数学成绩
	int Eng;//外语成绩
	int Com;//计算机成绩
public:
	student(){
		ID = NULL;
		Name = NULL;
		Math = 0;
		Eng = 0;
		Com = 0;
	}
	void Input(char *I,char *Nam,int Mat,int En,int Co){
		ID = I;
		Name = Nam;
		Math = Mat;
		Eng = En;
		Com = Co;
	}
	char *getID(){return ID;}
	void print(){
		cout<<"学生："<<Name<<"   学号："<<ID<<"   数学："<<Math<<"   英语："<<Eng<<"   计算机："<<Com<<endl;
	}
};
student search(char *I,student *stu){
	bool Compare;
	student obj;
	cout<<"I="<<I<<endl;
	int count2 = strlen(I);
	for (int j =0;j < 5;j++){
		Compare = true;
		int count1 = strlen(stu[j].getID());
		
		cout<<"count1="<<count1<<"   count2="<<count2<<endl;
		if (count1 != count2) Compare = false;
		else{
			cout<<"a="<<stu[j].getID()<<endl;
			if(strcmp(stu[j].getID(),I) != 0) Compare = false;
			cout<<"compare="<<strcmp(stu[j].getID(),I)<<endl;
		}
		if(Compare) return stu[j];
	}
	return obj;
}
int main(){
	cout<<"请输入5学生信息（）："<<endl;
	student stu[5];
	char *ID;
	char *Name;
	int Math;
	int Eng;
	int Com;
	for (int i = 0;i < 5;i++){
		cout<<"学生"<<i+1<<":"<<endl;
		ID = new char;
		Name = new char;
		cout<<"学号:";
		cin>>ID;
		cout<<"姓名：";
		cin>>Name;
		cout<<"数学：";
		cin>>Math;
		cout<<"英语：";
		cin>>Eng;
		cout<<"计算计：";
		cin>>Com;
		stu[i].Input(ID,Name,Math,Eng,Com);
	}
	cout<<"请输入您想搜索的学生的学号（ID）：";
	cin>>ID;
	cout<<"该学生信息是："<<endl;
	student obj = search(ID,stu);
	if (obj.getID() != NULL) obj.print();
	else
		cout<<"未找到！"<<endl;
    return 0;
}

