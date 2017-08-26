#include <stdio.h>
#include <math.h>   // sqrt
#include <limits.h> // INT_MAX
#include <stdlib.h> // atoi

#define IN 1
#define OUT !IN

typedef struct{int x, y;} Node;

int distance(Node i, Node j)
{
  double xd = i.x-j.x, yd = i.y-j.y;
  return (int)(sqrt(xd*xd+yd*yd) + 0.5);
}

void arrayInsert(int a[], int s, int t, int x)
{ // 配列をずらして挿入
  int i;
  for(i = t; i > s+1; i--) a[i] = a[i-1];
  a[s+1] = x;
}

int main(int argc, char *argv[])
{
  if(argc != 3) return 0; // ノード数 開始ノード番号 を引数にとる
  
  int N = atoi(argv[1]); // ノード数
  int i, j, k, dummy;
  Node A[N];
  int state[N], solution[N], edge[N][N];
  for(i = 0; i < N; i++)
    scanf("%d%d%d", &dummy, &A[i].x, &A[i].y);
  
  /* 全ての辺の重みを計算 */
  for(i = 0; i < N-1; i++)
    for(j = i+1; j < N; j++)
      edge[i][j] = edge[j][i] = distance(A[i], A[j]);
  
  /* 初期化 */
  for(i = 0; i < N; i++) state[i] = OUT;
  state[atoi(argv[2])-1] = IN;
  solution[0] = atoi(argv[2])-1;
  int min_cost = edge[solution[0]][solution[0]] = INT_MAX;
  int nearest_node;
  for(i = 0; i < N; i++){
    if(edge[solution[0]][i] < min_cost){
      min_cost = edge[solution[0]][i];
      nearest_node = i;
    }
  }
  state[nearest_node] = IN;
  solution[1] = nearest_node;

  int rep_node_num;
  for(i = 2; i < N; i++){
    min_cost = INT_MAX;
    for(j = 0; j < i; j++){
      for(k = 0; k < N; k++){
        if(state[k] == IN) continue;
        if(edge[solution[j]][k] < min_cost){
          min_cost = edge[solution[j]][k];
          nearest_node = k;
          rep_node_num = j;
        }
      }
    }
    state[nearest_node] = IN;
    arrayInsert(solution, rep_node_num, i, nearest_node);
  }
  
  int cost = edge[solution[0]][solution[N-1]];
  for(i = 1; i < N; i++) cost += edge[solution[i-1]][solution[i]];

  /* コマンドラインなどで確認するときにアンコメント */
  for(i = 0; i < N; i++)
    printf("%d\n", solution[i]+1);
  printf("cost = %d\n", cost);
  
  /* ファイルに結果を出力するときにアンコメント */
  FILE *fp;
  char *filename = "Ex5-1_na_ans.txt";
  fp = fopen(filename, "w");
  for(i = 0; i < N; i++)
    fprintf(fp, "%d %d %d\n", solution[i]+1, A[solution[i]].x, A[solution[i]].y);
  fprintf(fp, "%d\n", cost);
  
  return 0;
}
