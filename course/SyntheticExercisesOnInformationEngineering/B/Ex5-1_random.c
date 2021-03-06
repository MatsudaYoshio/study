#include <stdio.h>
#include <math.h>   // sqrt
#include <limits.h> // INT_MAX
#include <stdlib.h> // atoi
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

#define IN 1
#define OUT !IN

typedef struct{int x, y;} Node;

int distance(Node i, Node j)
{
  double xd = i.x-j.x, yd = i.y-j.y;
  return (int)(sqrt(xd*xd+yd*yd) + 0.5);
}

int irandom(int lb, int ub)
{
  return lb + (random()%(ub - lb + 1));
}

void permutation(int a[], int n)
{
  int i, r, tmp;
  for(i = 0; i < n; i++) a[i] = i;
  for(i = n-1; i > 0; i--){
    r = irandom(0,i);
    tmp = a[r];
    a[r] = a[i];
    a[i] = tmp;
  }
}

int main(int argc, char *argv[])
{
  struct timeval tm;
  gettimeofday(&tm, NULL);
  srandom((unsigned)((tm.tv_sec|tm.tv_usec)*getpid()));
  
  if(argc != 2) return 0; // ノード数を引数にとる
  
  int N = atoi(argv[1]); // ノード数
  int i, dummy;
  Node A[N];
  int solution[N];
  for(i = 0; i < N; i++)
    scanf("%d%d%d", &dummy, &A[i].x, &A[i].y);
  
  permutation(solution, N);
  
  int cost = distance(A[solution[0]], A[solution[N-1]]);
  for(i = 1; i < N; i++)
    cost += distance(A[solution[i-1]], A[solution[i]]);

  /* コマンドラインなどで確認するときにアンコメント */
  for(i = 0; i < N; i++)
    printf("%d\n", solution[i]+1);
  printf("cost = %d\n", cost);

  /* ファイルに結果を出力するときにアンコメント */
  //FILE *fp;
  //char *filename = "Ex5-1_random_ans.txt";
  //fp = fopen(filename, "w");
  //for(i = 0; i < N; i++)
  //  fprintf(fp, "%d %d %d\n", solution[i]+1, A[solution[i]].x, A[solution[i]].y);
  //fprintf(fp, "%d\n", cost);
  
  return 0;
}
