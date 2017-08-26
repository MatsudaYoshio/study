/* ランダムな問題例の作成 */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

int isCover(int a[], int n)
{ // 配列が全て1かどうかチェックする
  int i;
  for(i = 0; i < n; i++) if(!a[i]) return 0;
  return 1;
}

int irandom(int lb, int ub)
{ // 乱数生成
  return lb + (random()%(ub - lb + 1));
}

int main(void)
{
  
  struct timeval tm;
  FILE *fp;
  int i, j, N, M;
  scanf("%d%d", &N, &M);
  double S_cost[M];
  int S[M][N], S_size[M], Sum[N];

  /* 乱数生成の準備 */
  gettimeofday(&tm, NULL);
  srandom((unsigned)((tm.tv_sec|tm.tv_usec)*getpid()));
  
  while(!isCover(Sum,N)){ // 解のない問題になったらループして作り直す
    memset(Sum,0,sizeof(Sum));
    for(i = 0; i < M; i++){
      S_size[i] = 0;
      for(j = 0; j < N; j++){
        if(irandom(0,1)){
          S_size[i]++;
          Sum[j] = S[i][j] = 1;
        }else{
          S[i][j] = 0;
        }
      }
    }
  }

  for(i = 0; i < M; i++) S_cost[i] = irandom(100,100000)/100.0; // コストを1~1000の範囲(小数第2位まで)にする

  /* ファイルに書き出す */
  fp = fopen("testcase.txt","w");
  fprintf(fp, "%d\n%d\n", N, M);
  for(i = 0; i < M; i++){
    fprintf(fp, "%d\n%g\n", S_size[i], S_cost[i]);
    for(j = 0; j < N; j++)
      if(S[i][j]) fprintf(fp, "%d ", j+1);
    fprintf(fp, "\n");
  }
  fclose(fp);
  
  return 0;
}
