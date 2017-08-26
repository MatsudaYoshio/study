#include <stdio.h>
#include <time.h>   // clock
#include <math.h>   // sqrt
#include <limits.h> // INT_MAX
#include <string.h> // memcpy

#define N 12

typedef struct{int x, y;} Node; // ノード(各都市を表す)

int edge[N][N];
Node city[N];
int p[N]; // 全列挙するための配列
int solution[N];
int cost = INT_MAX;

int distance(Node i, Node j);
void init();
void swap(int a[], int x, int y);
int calCost();
int solve(int n);

int main(void)
{
  int i, node_num; // node_numはノード番号
  clock_t start, end; // 実行時間の計測に用いる変数
  
  /* 入力を受け取る */
  for(i = 0; i < N; i++)
    scanf("%d%d%d", &node_num, &city[i].x, &city[i].y);
  
  init(); // 初期化
  
  start = clock();
  printf("cost = %d\n", solve(N-1));
  end = clock();

  /* 最適な巡回路を表示 */
  for(i = 0; i < N; i++)
    printf("%d\n", solution[i]+1);
  
  printf("%.8f秒\n", (double)(end-start)/CLOCKS_PER_SEC); // 実行時間の表示
  
  return 0;
}

int distance(Node i, Node j)
{ // 距離を求める
  double xd = i.x-j.x, yd = i.y-j.y;
  return (int)(sqrt(xd*xd+yd*yd) + 0.5);
}

void init()
{
  int i, j;
  for(i = 0; i < N; i++) p[i] = i; // 順列を作成する準備として初期化

  /* あらかじめ全ての辺の重みを計算して配列に保存しておく */
  for(i = 0; i < N-1; i++)
    for(j = i+1; j < N; j++)
      edge[i][j] = edge[j][i] = distance(city[i], city[j]);
}

void swap(int a[], int x, int y)
{
  int tmp;
  tmp = a[x];
  a[x] = a[y];
  a[y] = tmp;
}

int calCost(int a[])
{ // 巡回路長を計算
  int i, cost;
  for(i = 1, cost = edge[a[0]][a[N-1]]; i < N; i++)
    cost += edge[a[i-1]][a[i]];
  return cost;
}

int solve(int n)
{
  int i;
  if(n <= 1){
    if(p[0] < p[N-2]){
      int new_cost = calCost(p);
      if(cost > new_cost){ // より最適な巡回路が見つかった場合
        cost = new_cost;
        memcpy(solution, p, sizeof(int)*N);
      }
    }
  }else{
    for(i = 0; i < n; i++){
      swap(p,i,n-1);
      solve(n-1);
      swap(p,n-1,i);
    }
  }
  return cost;
}
