/* 最近傍法 */
#include <stdio.h>
#include <math.h>   // sqrt
#include <limits.h> // INT_MAX
#include <stdlib.h> // atoi

/* 巡回路に入れたかどうかを示すためのフラグ */
#define IN 1
#define OUT !IN

typedef struct{int x, y;} Node; // ノード(各都市を表す)

int distance(Node i, Node j)
{ // 距離を求める
  double xd = i.x-j.x, yd = i.y-j.y;
  return (int)(sqrt(xd*xd+yd*yd) + 0.5);
}

int main(int argc, char *argv[])
{
  if(argc != 3) return 0; // ノード数 開始ノード番号 を引数にとる
  
  int cost = 0; // 合計コスト
  int N = atoi(argv[1]); // ノード数
  int i, j, node_num;
  Node A[N];
  int state[N], solution[N], edge[N][N];
  for(i = 0; i < N; i++)
    scanf("%d%d%d", &node_num, &A[i].x, &A[i].y);
  
  /* あらかじめ全ての辺の重みを計算して配列に保存しておく */
  for(i = 0; i < N-1; i++)
    for(j = i+1; j < N; j++)
      edge[i][j] = edge[j][i] = distance(A[i], A[j]);

  /* 初期化 */
  for(i = 0; i < N; i++) state[i] = OUT;
  state[atoi(argv[2])-1] = IN;
  solution[0] = atoi(argv[2])-1;
  
  for(i = 1; i < N; i++){
    int min_cost = INT_MAX, nearest_node;
    for(j = 0; j < N; j++){
      if(state[j] == IN) continue;
      if(edge[solution[i-1]][j] < min_cost){
        min_cost = edge[solution[i-1]][j];
        nearest_node = j;
      }
    }
    state[nearest_node] = IN;
    cost += min_cost;
    solution[i] = nearest_node;
  }

  cost += edge[solution[N-1]][0];

  /* コマンドラインなどで確認する */
  for(i = 0; i < N; i++)
    printf("%d\n", solution[i]+1);
  printf("cost = %d\n", cost);
  
  /* ファイルに結果を出力する */
  FILE *fp;
  char *filename = "Ex5-1_nn_ans.txt";
  fp = fopen(filename, "w");
  for(i = 0; i < N; i++)
    fprintf(fp, "%d %d %d\n", solution[i]+1, A[solution[i]].x, A[solution[i]].y);
  fprintf(fp, "%d\n", cost);
  
  return 0;
}
