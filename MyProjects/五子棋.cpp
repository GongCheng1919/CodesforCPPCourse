#include<iostream>
#include<cstdlib> 
#include <cstring>
using namespace std;
// const char outstr[11][4]={"??","??","??","??","??","??","??","??","??","??","??"};
const char outstr[11][5]={"??-","-??-","-??","??-","-??-","-??","??-","-??-","-??","-??-","-??-"};
int com[15][15],luozi[15][15];
int c,d;
void jushi()                                   //?????§Ø?????????????? 
{      
	int x,y,i,m,n,lianzi1=0,lianzi2=0,life=0;      
	memset(com,0,sizeof(com));      

	for(x=0;x<=14;x++)      
		for(y=0;y<=14;y++)      
		{          
			if(luozi[x][y]==0)          
			{              
				for(m=-1;m<=1;m++)               
					for(n=-1;n<=1;n++)              
					{              
						if(m!=0 || n!=0)              
						{                             
							for(i=1;i<=4;i++)                     
							{                           
								if( x+i*m>=0 && x+i*m<=14 && y+i*n>=0 && y+i*n<=14 && luozi[x+i*m][y+i*n]==1 )                          
								{lianzi1++;}                           
								else                           
									if(luozi[x+i*m][y+i*n]==0)                           
									{life++; break;}                           
									else                           
									{break;}}                                          
							for(i=-1;i>=-4;i--)                      
							{                           
								if( x+i*m>=0 && x+i*m<=14 && y+i*n>=0 && y+i*n<=14 && luozi[x+i*m][y+i*n]==1 )                           
								{lianzi1++;}                           
								else                           
									if(luozi[x+i*m][y+i*n]==0)                           
									{life++; break;}                           
									else                           
									{break;}                      
							}                      
							if(lianzi1==1)    
							{com[x][y]+=1;}                      
							else 
								if(lianzi1==2)                                
								{                                    
									if(life==1)   
									{com[x][y]+=5;}                                    
									else 
										if(life==2)   
										{com[x][y]+=10;}}                      
								else 
									if(lianzi1==3)                               
									{                                    
										if(life==1)   
										{com[x][y]+=20;}                                   
										else 
											if(life==2)   
											{com[x][y]+=100;}                               
									}                      
									else 
										if(lianzi1==4)    
										{com[x][y]+=500;}                      
										life=0;                              
										for(i=1;i<=4;i++)
										{                          
											if( x+i*m>=0 && x+i*m<=14 && y+i*n>=0 && y+i*n<=14 && luozi[x+i*m][y+i*n]==2 )   
											{lianzi2++;}                         
											else                          
												if(luozi[x+i*m][y+i*n]==0)      
												{
													life++; 
													break;
												}                       
												else             
												{break;}
										}                                       
										for(i=-1;i>=-4;i--)            
										{                        
											if( x+i*m>=0 && x+i*m<=14 && y+i*n>=0 && y+i*n<=14 && luozi[x+i*m][y+i*n]==2 )   
											{lianzi2++;}                         
											else                        
												if(luozi[x+i*m][y+i*n]==0)   
												{life++; break;}               
												else                         
												{break;}                 
										}                    
										if(lianzi2==1)   
										{com[x][y]+=2;}      
										else if(lianzi2==2)   
										{                      
											if(life==1) 
											{com[x][y]+=8;}  
											else if(life==2)  
											{com[x][y]+=30;}         
										}
										else if(lianzi2==3)         
										{                            
											if(life==1)  
											{com[x][y]+=50;}     
											else if(life==2)  
											{com[x][y]+=200;}     
										}                     
										else if(lianzi2==4)   
										{com[x][y]+=1000;}   
										lianzi1=0;                  
										lianzi2=0;                    
										life=0;             
						}          
					}         
			}        
		}             
 }
void computer(int a[15][15])           //??????????????? 
{      
	int i,j,max=0;      
	jushi();      
	for(i=0;i<=14;i++)     
		for(j=0;j<=14;j++)      
		{          
			if(com[i][j]>max)          
			{                     
				max=com[i][j];                     
				c=i;                     
				d=j;         
			}     
		}      
		a[c][d]=10;      
		luozi[c][d]=2;}
int panduan(int x,int y,int sum)         //?§Ø????????? 
{     
	int m,n,i,lianzi=0;              
	for(m=-1;m<=1;m++)              
		for(n=-1;n<=1;n++)              
		{              
			if(m!=0 || n!=0)             
			{                      
				for(i=1;i<=4;i++)                     
				{                           
					if( x+i*m>=0 && x+i*m<=14 && y+i*n>=0 && y+i*n<=14 && luozi[x+i*m][y+i*n]==sum )                           
					{lianzi++;}                          
					else                           
					{break;}                     
				}                                        
				for(i=-1;i>=-4;i--)                   
				{                           
					if( x+i*m>=0 && x+i*m<=14 && y+i*n>=0 && y+i*n<=14 && luozi[x+i*m][y+i*n]==sum )     
					{lianzi++;}                          
					else                          
					{break;}                    
				}                      
				if(lianzi>=4)
				{                    
					return 1;                 
				}                   
				else                     
				{                    
					lianzi=0;          
				}            
			}             
		}             
		return 0;   
}int main()              //?????? ?????????????????? 
{ 
	system ("color 2f"); 
	system ("mode con cols=50 lines=25"); 
	system ("title ???????");     
	int a[15][15]={0,1,1,1,1,1,1,1,1,1,1,1,1,1,2,                   
		3,4,4,4,4,4,4,4,4,4,4,4,4,4,5,                   
		3,4,4,4,4,4,4,4,4,4,4,4,4,4,5,                   
		3,4,4,4,4,4,4,4,4,4,4,4,4,4,5,                   
		3,4,4,4,4,4,4,4,4,4,4,4,4,4,5,                  
		3,4,4,4,4,4,4,4,4,4,4,4,4,4,5,                   
		3,4,4,4,4,4,4,4,4,4,4,4,4,4,5,                   
		3,4,4,4,4,4,4,4,4,4,4,4,4,4,5,                   
		3,4,4,4,4,4,4,4,4,4,4,4,4,4,5,                  
		3,4,4,4,4,4,4,4,4,4,4,4,4,4,5,    
        3,4,4,4,4,4,4,4,4,4,4,4,4,4,5,        
		3,4,4,4,4,4,4,4,4,4,4,4,4,4,5,               
		3,4,4,4,4,4,4,4,4,4,4,4,4,4,5,               
		3,4,4,4,4,4,4,4,4,4,4,4,4,4,5,                
		6,7,7,7,7,7,7,7,7,7,7,7,7,7,8};    
	int x,y,i,j;     
	memset(luozi,0,sizeof(luozi));    
	char cols_name[50] = " 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14";
	cout<<cols_name<<endl; 
    for(i=0;i<=14;i++)   
	{                
		if(i!=0)             
			cout<<endl;               
		if (i<10) cout<<" "<<i; else cout<<i;   ;                 
		for(j=0;j<=14;j++)               
		{cout<<outstr[a[i][j]];              
		}   
	}    
	cout<<endl;   
	cout<<"???????????????? ??\\?? ???????:";          
	while(cin>>x>>y)     
	{        
		if(luozi[x][y]==0 && x>=0 && x<=14 && y>=0 && y<=14)     
		{            
			a[x][y]=9;        
			luozi[x][y]=1;    
			if(panduan(x,y,1)==0)    
			{              
				system ("cls");   
				computer(a);        
				if(panduan(c,d,2)==0)   
				{               
					cout<<cols_name<<endl;      
					for(i=0;i<=14;i++)               
					{             
						if(i!=0)            
							cout<<endl;
						if (i<10) cout<<" "<<i;
						else cout<<i;    
						for(j=0;j<=14;j++)      
						{                   
							cout<<outstr[a[i][j]];   
						}                
					}               
					cout<<endl;    
					cout<<"????????????"<<x<<"??"<<" "<<y<<"??"<<endl;      
					cout<<"?????????????"<<c<<"??"<<" "<<d<<"??"<<endl;   
					cout<<"????????????????";      
				}               
				else             
				{              
					cout<<cols_name<<endl;     
					for(i=0;i<=14;i++)              
					{                
						if(i!=0)              
							cout<<endl;           
						if (i<10)        
							cout<<" "<<i;
						else cout<<i;            
						for(j=0;j<=14;j++)         
						{                     
							cout<<outstr[a[i][j]];  
						}               
					}                
					cout<<endl;          
					cout<<"?????????????"<<c<<"??"<<" "<<d<<"??"<<endl;   
					cout<<"??????!"<<endl;     
					break;             
				}               
			}            
			else 
            {             
				system ("cls");                 //????                 
				cout<<cols_name<<endl;     
				for(i=0;i<=14;i++)           
				{                 if(i!=0)     
				cout<<endl;                 
				if (i<10)        
					cout<<" "<<i;
				else cout<<i;                
				for(j=0;j<=14;j++)         
				{                     
					cout<<outstr[a[i][j]];       
				}               
				}                
				
				cout<<endl;     
				cout<<"???????!"<<endl;   
				break;           
			}       
		}    
		else      
			{           
			cout<<"?????????????????:"<<endl;   
      }      
    } 
	system ("title §Ý§Ý????"); 
	system ("color 03");  
	cout<<"§Ý§Ý???"<<endl;   
	system("pause>nul");   
	return 0;
}
