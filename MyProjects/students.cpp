//The First Work
/************************************************************************************
			���ѧ����(Student)�����ݳ�Ա��ѧ�š�������ɼ�(��ѧ������������)��
		�����������������룻�����ѧ��Ϊ����������������������������������
		ѧ����Ϣ
*************************************************************************************/
#include<iostream>
#include<string.h>
using namespace std;
class student{
private:
	char *ID;//ѧ��
	char *Name;//����
	int Math;//��ѧ�ɼ�
	int Eng;//����ɼ�
	int Com;//������ɼ�
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
		cout<<"ѧ����"<<Name<<"   ѧ�ţ�"<<ID<<"   ��ѧ��"<<Math<<"   Ӣ�"<<Eng<<"   �������"<<Com<<endl;
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
	cout<<"������5ѧ����Ϣ������"<<endl;
	student stu[5];
	char *ID;
	char *Name;
	int Math;
	int Eng;
	int Com;
	for (int i = 0;i < 5;i++){
		cout<<"ѧ��"<<i+1<<":"<<endl;
		ID = new char;
		Name = new char;
		cout<<"ѧ��:";
		cin>>ID;
		cout<<"������";
		cin>>Name;
		cout<<"��ѧ��";
		cin>>Math;
		cout<<"Ӣ�";
		cin>>Eng;
		cout<<"����ƣ�";
		cin>>Com;
		stu[i].Input(ID,Name,Math,Eng,Com);
	}
	cout<<"����������������ѧ����ѧ�ţ�ID����";
	cin>>ID;
	cout<<"��ѧ����Ϣ�ǣ�"<<endl;
	student obj = search(ID,stu);
	if (obj.getID() != NULL) obj.print();
	else
		cout<<"δ�ҵ���"<<endl;
    return 0;
}

