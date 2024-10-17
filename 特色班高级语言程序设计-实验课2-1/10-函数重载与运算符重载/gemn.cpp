#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<random>
using namespace std;
template<typename T>
void cheng(int n, int m);
template<typename T>
void cheng(int n, int m)
{
	mt19937 generate(0);
	uniform_real_distribution<T> u(0.0, 1.0);
	T** p1, ** p2, ** p3;
	int i, j, z;
	p1 = (T**)malloc(n * sizeof(T*));
	p3 = (T**)malloc(n * sizeof(T*));
	p2 = (T**)malloc(n * sizeof(T*));
	if (p1 == NULL || p2 == NULL || p3 == NULL) printf("error");
	for (i = 0; i < n; i++)
	{
		p1[i] = (T*)malloc(m * sizeof(T));
		p2[i] = (T*)malloc(m * sizeof(T));
		p3[i] = (T*)malloc(m * sizeof(T));
		if (p1[i] == NULL || p3[i] == NULL||p2[i] == NULL) printf("error");
	}
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			 p1[i][j]=u(generate);
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			p2[i][j]=u(generate);
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			p3[i][j] = p1[i][j]+p2[i][j];
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			if (j == 0)cout << p3[i][j];
			else cout << ' ' << p3[i][j];
		}
		if (i != n - 1)printf("\n");
	}
	free(p1);
	free(p2);
	free(p3);
}
template<>
void cheng<int>(int n, int m)
{
	mt19937 generate(0);
	uniform_int_distribution<int> u(1,100);
	int** p1, ** p2, ** p3;
	int i, j, z;
	p1 = (int**)malloc(n * sizeof(int*));
	p3 = (int**)malloc(n * sizeof(int*));
	p2 = (int**)malloc(n * sizeof(int*));
	if (p1 == NULL || p2 == NULL || p3 == NULL) printf("error");
	for (i = 0; i < n; i++)
	{
		p1[i] = (int*)malloc(m * sizeof(int));
		p2[i] = (int*)malloc(m * sizeof(int));
		p3[i] = (int*)malloc(m * sizeof(int));
		if (p1[i] == NULL || p3[i] == NULL||p2[i]==NULL) printf("error");
	}
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			p1[i][j] = u(generate);
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			p2[i][j] = u(generate);
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			p3[i][j] = p1[i][j] + p2[i][j];
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			if (j == 0)cout << p3[i][j];
			else cout << ' ' << p3[i][j];
		}
		if (i != n - 1)printf("\n");
	}
	free(p1);
	free(p2);
	free(p3);
}
int main()
{
	int n, m;
	char c;
	cin >> n >> m  >> c;
	switch (c)
	{
	case'i':cheng<int>(n, m); break;
	case'f':cheng<float>(n, m); break;
	case'd':cheng<double>(n, m); break;
	}
	return 0;
}
