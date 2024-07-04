#include <iostream>
#include <stdlib.h>
using namespace std;
struct circle
{
  int row;      // 点的行数
  int rank;     // 点的列数
  int feature;  // 点的属性（可通过性，停留时间）
  int lastrow;  // 前一点的行数
  int lastrank; // 前一点的列数
  int length;   // 到该点的最短步长，应该是前一点的该项加上本点的feature再+1
  int isok;     // 判断是否找到最短路径，0没找到，1找到
  // int beside[4];    // 这里存储的是相邻点，即上下左右四个点<row+-1,rank+-1>，初始化为1，
};
int main()
{
  // 思路
  // 1：输入行数和列数，构造circle类型的数组，初始化row，rank，feature，oracle，oracle的初始化应当在所有初始属性初始化之后，也即要有两个循环
  int n, m;
  cin >> n >> m;
//   struct circle t[n][m];
    // Create a pointer to a pointer to 'circle'
    circle** t = new circle*[n];

    // For each pointer, create an array of 'circle'
    for(int i = 0; i < n; ++i)
        t[i] = new circle[m];
  int j = 0;
  int i, p, q;
  for (i = 0; i < m; i++) // 初始化点的行列以及属性
  {
    char c;
    cin >> c;
    t[j][i].row = i;
    t[j][i].rank = j;
    t[j][i].isok = 0;
    t[j][i].length = 99999;
    // t[j][i].beside={1,1,1,1};
    if (c == 'X')
      t[j][i].feature = 99999;
    else if (c == '.')
      t[j][i].feature = 0;
    else
      t[j][i].feature = (int)c - (int)'0';
    if (i == m - 1)
    {
      i = -1;
      j++;
    }
    if (j == n)
      break;
  }
  j = 0;
  i = 0;
  int temp;
  int t_rank, t_row;
  j = 0;
  t_rank = 0;
  t_row = 0;
  // 2：从<0,0>出发，遍历每一个能到达的点，也即非‘x'的点，该步应初始化lastrow和lastrank以及length，oracle应当-1，因为不会返回初始点
  while (t[n - 1][m - 1].isok != 1)
  {

    if (j == 0 && i == 0)
    {
      t[j][i].length = 0;
      t[j][i].isok = 1;
      j++;
      i++;
      continue;
    }

    // 上 t_rank-1,t_row
    if (t_rank - 1 >= 0)
    {
      temp = t[t_rank][t_row].length + 1 + t[t_rank][t_row].feature;
      if (temp < t[t_rank - 1][t_row].length) // 判断该点到上方的点是否比现有路径的长度短，下同
      {
        t[t_rank - 1][t_row].length = temp;                    // 如果比现有路径短，则将长度改为当前路径
        t[t_rank - 1][t_row].lastrank = t[t_rank][t_row].rank; // 以当前点为前一点，录入行列
        t[t_rank - 1][t_row].lastrow = t[t_rank][t_row].row;
      }
    }
    // 下t_rank+1，t_row
    if (t_rank + 1 < n)
    {
      temp = t[t_rank][t_row].length + 1 + t[t_rank][t_row].feature;
      if (temp < t[t_rank + 1][t_row].length)
      {
        t[t_rank + 1][t_row].length = temp;
        t[t_rank + 1][t_row].lastrank = t[t_rank][t_row].rank;
        t[t_rank + 1][t_row].lastrow = t[t_rank][t_row].row;
      }
    }
    // 左t_row-1,t_rank
    if (t_row - 1 >= 0)
    {
      temp = t[t_rank][t_row].length + 1 + t[t_rank][t_row].feature;
      if (temp < t[t_rank][t_row - 1].length)
      {
        t[t_rank][t_row - 1].length = temp;
        t[t_rank][t_row - 1].lastrank = t[t_rank][t_row].rank;
        t[t_rank][t_row - 1].lastrow = t[t_rank][t_row].row;
      }
    }
    // 右t_row+1,t_rank
    if (t_row + 1 < m)
    {
      temp = t[t_rank][t_row].length + 1 + t[t_rank][t_row].feature;
      if (temp < t[t_rank][t_row + 1].length)
      {
        t[t_rank][t_row + 1].length = temp;
        t[t_rank][t_row + 1].lastrank = t[t_rank][t_row].rank;
        t[t_rank][t_row + 1].lastrow = t[t_rank][t_row].row;
      }
    }
    p = 0;
    q = 0;
    int judge = 999999;

    for (p = 0; p < m; p++) // 比较所有不确定最短路径的点，找出路径最短的点并标记
    {
      if (t[q][p].isok == 1) // 如果是已经确定最短路径的点，则下一个
      {
        if (p == m - 1)
        {
          p = -1;
          q++;
        }
        if (q == n)
          break;
        continue;
      }
      if (t[q][p].length < judge) // 判断路径是否较短，并记录当前最短路径的长度和坐标
      {
        judge = t[q][p].length;
        t_rank = t[q][p].rank;
        t_row = t[q][p].row;
      }
      if (p == m - 1)
      {
        p = -1;
        q++;
      }
      if (q == n)
      {
        t[t_rank][t_row].isok = 1; // 通过坐标标记确定最短路径的点
        break;
      }
    }
    t[t_rank][t_row].isok = 1; // 同上
  }
  t_rank = n - 1;
  t_row = m - 1;
  int out[100][2];
  // 确定了目标点的最短路径，则要从终点依次向前取前一点坐标，直到取到起点
  p = 0;
  q = 0;
  int ct = 0;
  while (t_rank != 0 || t_row != 0)
  {
    out[p][q] = t[t_rank][t_row].rank;
    out[p][q + 1] = t[t_rank][t_row].row;
    ct++; // 记录数组可能长度
    p++;  // 行数加一
    i = t_rank;
    j = t_row;
    t_rank = t[i][j].lastrank;
    t_row = t[i][j].lastrow;
  }
  out[ct][0] = 0;
  out[ct][1] = 0;
  p = 0;
  for (i = ct; i > 0; i--) // 数一共需要多少步
  {
    if (t[out[i][0]][out[i][1]].feature == 0)
    {
      p++;
    }
    else
    {
      for (q = 0; q < t[out[i][0]][out[i][1]].feature; q++)
      {
        p++;
      }
      p++;
    }
  }
  cout << "到达目标需要" << p << "步，具体路径为" << endl;
  for (i = ct; i > 0; i--)
  {
    if (t[out[i][0]][out[i][1]].feature == 0) // 如果是'.'，则输出
    {
      cout << p << ":"
           << "(" << out[i][0] << "," << out[i][1] << ")"
           << "->(" << out[i - 1][0] << "," << out[i - 1][1] << ")" << endl;
      p++;
    }
    else
    {
      for (q = 0; q < t[out[i][0]][out[i][1]].feature; q++) // 如果是数字，则输出
      {
        cout << p << ":"
             << "FIGHT AT (" << out[i][0] << "," << out[i][1] << ")" << endl;
        p++;
      }
      cout << p << ":" // 在数字之后，输出下一项
           << "(" << out[i][0] << "," << out[i][1] << ")"
           << "->(" << out[i - 1][0] << "," << out[i - 1][1] << ")" << endl;
      p++;
    }
  }
  // For each array of 'circle', delete it
for(int i = 0; i < n; ++i)
    delete [] t[i];

// Delete the array of pointers
delete [] t;
  return 0;
}