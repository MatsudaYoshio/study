/* 改善法 */
#include <stdio.h>
#include <math.h>   // sqrt
#include <stdlib.h> // atoi
#include <string.h>

#define IN 1
#define OUT !IN

const int OPT = 26130; // 最適解のコスト
const int ITE_N = 1000; // 想定するイテレーション数

typedef struct{int x, y;} Node;

int distance(Node i, Node j)
{
  double xd = i.x-j.x, yd = i.y-j.y;
  return (int)(sqrt(xd*xd+yd*yd) + 0.5);
}

void swap(int *x, int *y)
{
  int tmp;
  tmp = *x;
  *x = *y;
  *y = tmp;
}

void reverse(int a[], int l, int r)
{
  while(l < r){
    swap(&a[l], &a[r]);
    l++;
    r--;
  }
}

int main(int argc, char *argv[])
{
  if(argc != 2) return 0; // ノード数を引数にとる
  
  int cost; // 合計コスト
  int N = atoi(argv[1]); // ノード数
  int i, j, k;
  Node A[N];
  int solution[N], edge[N][N];
  int new_solution[N], new_cost, x, y;
  for(i = 0; i < N; i++){
    scanf("%d", &solution[i]);
    solution[i]--;
    scanf("%d%d", &A[solution[i]].x, &A[solution[i]].y);
  }
  scanf("%d", &cost);

  /* 全ての辺の重みを計算 */
  for(i = 0; i < N-1; i++)
    for(j = i+1; j < N; j++)
      edge[i][j] = edge[j][i] = distance(A[i], A[j]);

  int ite = 0;
  double R[ITE_N]; // 誤差率
  for(i = 0; i < ITE_N; i++) R[i] = -1;
  int flag;
  
  do{
    flag = 0;
    for(i = 0; i < N; i++){
      for(j = 0; j < N; j++){
        if(i == j || i == (j+1)%N || j == (i+1)%N) continue;
        x = i;
        y = j;
        if(x > y) swap(&x, &y);
        memcpy(new_solution, solution, sizeof(int)*N);
        reverse(new_solution, x+1, y);
        new_cost = edge[new_solution[0]][new_solution[N-1]];
        for(k = 1; k < N; k++)
          new_cost += edge[new_solution[k-1]][new_solution[k]];
        if(new_cost < cost){
          flag = 1;
          R[ite] = (double)(new_cost - OPT) / (double)OPT * 100;
          ite++;
          cost = new_cost;
          memcpy(solution, new_solution, sizeof(int)*N);
          printf("[%d]iteration, cost = %d\n", ite, cost);
        }
      }
    }
  }while(flag);

  /* ファイルに結果を出力する */
  //FILE *fp;
  //char *filename = "Ex5-2_random_ans.txt";
  //fp = fopen(filename, "w");
  //for(i = 0; i < N; i++)
  //  fprintf(fp, "%d %d %d\n", solution[i]+1, A[solution[i]].x, A[solution[i]].y);
  //fprintf(fp, "%d %d %d\n", solution[0]+1, A[solution[0]].x, A[solution[0]].y);  // gnuplotで描画しやすいようにデータを入力
  //fclose(fp);
  
  /* 誤差率をファイルに出力する */
  FILE *fp;
  char *filename = "error_index.txt";
  fp = fopen(filename, "w");
  for(i = 0; i < ITE_N; i++){
    if(R[i] == -1){
      fprintf(fp, "%d %f\n", i+1, R[i-1]);
      R[i] = R[i-1];
    }else{
     fprintf(fp, "%d %f\n", i+1, R[i]);
    }
  }
  fclose(fp);
  
  return 0;
}
