/**************************************************************************
                              ����    ����
***************************************************************************/
#include<iostream>
#include<stdlib.h>
#include<iomanip>
using namespace std;
//1901.9.Ϊ���ȣ�W=0��
int main()
{
	int year,month,i,j,w,k,s,B;
	int ryear[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};
	int pyear[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	int A[13];
	char p,Y;
	cout<<"                                  ��ӭʹ�ù�������"<<endl<<endl;
	do 
	{
		cout<<"��������Ҫ����ݣ�";
	    cin>>year;
		if(year<=0)
		{
            cout << "�������������������ݣ�" << endl;
            continue;
        }
	    if (year%100==0)
		{
			if (year%400==0) {
				for(i=0;i<=12;i++) A[i]=ryear[i];
			    cout<<"�����꣡"<<endl;
			}
		    else {
				for(i=0;i<=12;i++) A[i]=pyear[i];
			    cout<<"��ƽ�꣡"<<endl;
			}
	//cout<<A[2]<<endl;
		}
		else {
			if (year%4==0){
				for(i=0;i<=12;i++) A[i]=ryear[i];
			    cout<<"�����꣡"<<endl;
			}
		    else {
				for(i=0;i<=12;i++) A[i]=pyear[i];
			    cout<<"��ƽ�꣡"<<endl;
			}
		    //cout<<A[2]<<endl;
		}
		if (year>1901)
		{
			s=122;
			for (k=1902;k<year;k++)
			{
				if (k%100==0) {
					if (k%400==0) B=366;
				    else B=365;
				}
				else {
					if (k%4==0) B=366;
			        else B=365;
				}
				//cout<<B<<endl;
		        s=s+B;
			}
		    //cout<<"s="<<s<<endl;
		}
		if (year==1901) s=2;
		if (year<1901)
		{
			s=243;
			for (k=1900;k>year;k--)
			{
				if (k%100==0) {
					if (k%400==0) B=366;
				    else B=365;
				}
				else {
					if (k%4==0) B=366;
			        else B=365;
				}
				//cout<<B<<endl;
		        s=s+B;
			}
			cout<<"s="<<s<<endl;
		}
		cout<<"���뿴����ȫ���������(y/n)";
		cin>>Y;
		while (Y!='y'&&Y!='n')
		{
			cout<<"���������";
		    cin>>Y;
		}
		if (Y=='y') 
		{
			for (j=0;j<12;j++)
			{
				cout<<j+1<<"�£�"<<endl;
				s=s+A[j];
				w=s%7;
				cout<<setw(7)<<"����"<<setw(7)<<"��һ"<<setw(7)<<"�ܶ�"<<setw(7)<<"����"<<setw(7)<<"����"<<setw(7)<<"����"<<setw(7)<<"����"<<endl;
	            for (i=0;i<(A[j+1]+w);i++)
				{
					if (i<w) cout<<setw(7)<<" ";
					else cout<<setw(7)<<(i-w+1);
			        if ((i+1)%7==0) cout<<endl;
				}
		        cout<<endl;
			}
			cout<<"�㻹����ʹ��һ���𣿣�y/n��";
		    cin>>p;
			while (p!='y'&&p!='n')
			{
			cout<<"�������������������ѡ��!��y/n��";
			cin>>p;
			}
		}
		else 
		{
			cout<<"�������·�(0->12)��";
	        cin>>month;
	        while (1>month||12<month)
			{
				cout<<"��������������������·�!��0->12��";
		        cin>>month;
			}
		    if (year>1901){
				for (i=0;i<month;i++) s=s+A[i];
			    w=s%7;
			}
		    if (year<1901) {
			    for (i=month;i<=12;i++) s=s+A[i];
				w=7-s%7;
			}
		    if (year==1901)
			{
			    for (i=0;i<month;i++) s=s+A[i];
			    w=s%7;
			}
		    cout<<setw(7)<<year<<"."<<month<<endl;
	        cout<<setw(7)<<"����"<<setw(7)<<"��һ"<<setw(7)<<"�ܶ�"<<setw(7)<<"����"<<setw(7)<<"����"<<setw(7)<<"����"<<setw(7)<<"����"<<endl;
	        for (i=0;i<(A[month]+w);i++)
			{
				if (i<w) cout<<setw(7)<<" ";
			    else cout<<setw(7)<<(i-w+1);
			    if ((i+1)%7==0) cout<<endl;
			}
			cout<<endl;
		    cout<<"�㻹����ʹ��һ���𣿣�y/n��";
		    cin>>p;
			while (p!='y'&&p!='n')
			{
			cout<<"�������������������ѡ��!��y/n��";
			cin>>p;
			}
		}
	}while (p=='y');
	cout<<"ллʹ�ã�ף��������֣�"<<endl;
	system("pause");
	return 0;
}
