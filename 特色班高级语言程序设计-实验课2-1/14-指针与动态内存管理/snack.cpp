#include<stdio.h>
int a[100][100];
int main()
{
	int n, i, j, t = 1;
	scanf("%d", &n);
	
	i = 0; j = 0;
	do {
		
		for (j; j<n-1 &&a[i][j + 1] == 0 ; j++)
		{
			a[i][j] = t; t++;
		}
		for (i;i<n-1 && a[i + 1][j] == 0 ; i++)
		{
			a[i][j] = t; t++;
		}
		for (j;j>=1 &&a[i][j - 1] == 0 ; j--)
		{
			a[i][j] = t; t++;
		}
		for (i;i>=1&& a[i - 1][j] == 0 ; i--)
		{
			a[i][j] = t; t++;
		}
	} while (t < n * n);
	if (n % 2 == 0) a[n / 2][n / 2 - 1] = n * n;
	else a[n / 2][n / 2] = n * n;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{   
			if (j == n-1)printf(" %d\n", a[i][j]);
			else printf(" %d", a[i][j]);
		}

	return 0;


}
