#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#define max(a,b) (((a)>=(b))?(a):(b))
#define min(a,b) (((a)<(b))?(a):(b))
// #include <windows.h>

void Clear()
{
    printf("\x1B[2J\x1B[H");
}

void DisplayArray16(int arr[16][16]){
	Clear();
	int i,j;
	for(i=0;i<16;i++){
		for(j=0;j<16;j++){
			if (arr[i][j]){
				// printf("%d ",arr[i][j]);
				printf("%c ",35);
			}
			else{
				printf("  ");
			}
		}
		printf("\n");
	}
}

void DisplayArray4(int arr[4][8]){
	int i,j;
	int temp;
	char str[10];
	itoa(254,str,2);
		printf("%08s \n",str);
	
	for(i=0;i<4;i++){
		for(j=0;j<8;j++){
			//itoa(arr[i][j],str,2);
			printf("%d\t",arr[i][j]);
		}
		printf("\n");
	}
	for(j=0;j<8;j++)
	{
		itoa(arr[0][j],str,2);
		printf("%08s ",str);
		itoa(arr[1][j],str,2);
		printf("%08s ",str);
		printf("\n");
	}
	printf("\n");
	for(j=0;j<8;j++)
	{
		itoa(arr[2][j],str,2);
		printf("%08s ",str);
		itoa(arr[3][j],str,2);
		printf("%08s",str);
		printf("\n");
	}
	//scanf("%c",&temp);
}
int sqare(int m,int n){
	int temp=1;
	int i=n;
	if(m==0) return 0;
	while(i>0){
		temp*=m;
		i=i-1;
	}
	return temp;
}
void Change16To4(int arr1[16][16],int arr2[4][8]){
	int i,j;
	//设置初值
	for(i=0;i<4;i++){
		for(j=0;j<8;j++){
			arr2[i][j]=0;
		}
	}
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			arr2[0][i]+=sqare(2*arr1[i][j],7-j);
		}
		for(j=0;j<8;j++){
			arr2[1][i]+=sqare(2*arr1[i][j+8],7-j);
		}
	}
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			arr2[2][i]+=sqare(2*arr1[i+8][j],7-j);
		}
		for(j=0;j<8;j++){
			arr2[3][i]+=sqare(2*arr1[i+8][j+8],7-j);
		}
	}
	 DisplayArray4(arr2);
}
int changeTheBoard(int arr[16][16],int m_boardSpace){
	//输入一个数
	int j;
	char temp;
	//先把前一次的置0
	for(j=0;j<5;j++){
		arr[15][m_boardSpace+j]=0;
	}
	printf("输入A实现接板左移，输入D实现接板右移\n");
	scanf("%c",&temp);
	printf("temp=%c\n",temp);
	if(temp=='a'||temp=='A'){
		if(m_boardSpace>1){
			m_boardSpace-=1;
		}
	}
	else
		if(temp=='d'||temp=='D'){
			if(m_boardSpace<9){
				m_boardSpace+=1;
			}
		}else
			printf("请输入正确的按键\n");

	for(j=0;j<5;j++){
		arr[15][m_boardSpace+j]=1;
	}
	
	DisplayArray16(arr);
	printf("------------------------------------\n");
	return m_boardSpace;
}

char check_key(){
	char cTake = 0;
	if (_kbhit())//非阻塞获取用户输入
	{
		cTake = _getch();//获取输入字符,并回显		
		if (cTake == '\r')
		{	
			printf("暂停游戏\n");
			system("pause");
		}
	}
	return cTake;
}

char _Sleep(int mtime){
	char cTake = 0;
	for(int i=0;i<mtime*100;i++){
		if (!cTake){
			cTake = check_key();
		}else{
			check_key();
		}
	}
	return cTake;
}

// @m_boardSpace:上一次控制板的位置
// @m_boardCount:控制板长度
int control_game(int arr[16][16],int m_boardSpace, int m_boardCount){
	char temp;
	char is_change = 0;
	// char cTake = check_key();
	char cTake = _Sleep(100);
	switch(cTake){
		case 0: break;
		case 'a':
		case 'A': m_boardSpace-=1; is_change =1; break;
		case 'd':
		case 'D': m_boardSpace+=1; is_change =1; break;
		default: printf("请输入正确的按键\n");
				 system("pause");
	}
	if (is_change){
		m_boardSpace=min(max(m_boardSpace,0),16-m_boardCount);
		for(int j=0;j<16;j++){
			if (j>=m_boardSpace && j<m_boardSpace+m_boardCount)
				arr[15][j]=1;
			else
				arr[15][j]=0;
		}
	}
	return m_boardSpace;
}

int main(){
	int m_displayArray[16][16];
	int m_displayArray4[4][8];
	int i,j;
	int x=14;
	int y=6;
	int inc_x=1;
	int inc_y=1;
	int m_boardSpace=7;
	int m_boardCount=5;

	//首先数组初始化
	for(i=0;i<16;i++){
		for(j=0;j<16;j++){
			m_displayArray[i][j]=0;
		}
	}
	//两边的列空出来作为边界
	for(i=0;i<16;i++){
			m_displayArray[i][0]=1;
			m_displayArray[i][15]=1;
	}
	//设置上面四行为存在方块
	for(i=0;i<4;i++){
		for(j=1;j<15;j++){
			m_displayArray[i][j]=1;
		}
	}
	//设置接板
	for(j=0;j<m_boardCount;j++){
		m_displayArray[15][m_boardSpace+j]=1;
	}
	//设置小球
	m_displayArray[x][y]=1;
	//显示数组
	DisplayArray16(m_displayArray);


	//打方块开始运行

	//设置x、y为当前小球的坐标
	while(1){
		// char cTake = check_key();
		m_boardSpace=control_game(m_displayArray,m_boardSpace,m_boardCount);
		// _Sleep(2000);
		m_displayArray[x][y]=0;
		if(y>=14||y<=1)
			inc_y=-inc_y;
		//y+=inc_y;
		if(x>=15)
		{
			printf("GAME OVER!\n");
			break;
		}
		if(x<=0)
			inc_x=-inc_x;
		//x+=inc_x;
		//此处说明碰到了“砖块”
		
		if(m_displayArray[x+inc_x][y+inc_y]==1&&x==14){
			inc_x=-inc_x;
			x=x+inc_x;
			y=y+inc_y;
		}
		//此时在顶部打方块儿
		else{

			if(m_displayArray[x+inc_x][y]==1||m_displayArray[x][y+inc_y]==1)
			{
				if(m_displayArray[x+inc_x][y]==1){
				m_displayArray[x+inc_x][y]=0;
				inc_x=-inc_x;
				//x=x+inc_x;
				//y=y+inc_y;
				
				}
			
				if(m_displayArray[x][y+inc_y]==1){
					m_displayArray[x][y+inc_y]=0;
					inc_y=-inc_y;
					//x=x+inc_x;
					//y=y+inc_y;
			
				}
			}
			else{
				if(m_displayArray[x+inc_x][y+inc_y]==1){
						m_displayArray[x+inc_x][y+inc_y]=0;
						//p判断回退是不是墙
						if(x!=0)
							inc_x=-inc_x;
						if(y!=1&&y!=14)
							inc_y=-inc_y;
						//x=x+inc_x;
						//y=y+inc_y;
				}
				//	x=x+inc_x;
				//	y=y+inc_y;
			}
			x=x+inc_x;
			y=y+inc_y;

		}
		m_displayArray[x][y]=1;
		DisplayArray16(m_displayArray);

		// Change16To4(m_displayArray,m_displayArray4);
		//DisplayArray4(m_displayArray4);
		//操作接板函数
		//m_boardSpace=changeTheBoard(m_displayArray,m_boardSpace);
	}
	return 0;
}