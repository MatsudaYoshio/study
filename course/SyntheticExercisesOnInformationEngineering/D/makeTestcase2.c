/*
  問題例(a)~(c)のパターンの問題例の作成

  bは3以上の入力のみを受け取る
  b = 3で問題例(a)と同じものを作成
  b = 4で問題例(b)と同じものを作成
  b = 5で問題例(c)と同じものを作成
*/
#include <stdio.h>
#include <string.h>

int main(void)
{
  FILE *fp;
  int i, j, b, N, M;
  scanf("%d", &b);
  if(b < 3) return 0;
  N = (1<<(b+1))-2;
  M = b+2;
  double S_cost[M];
  int S[M][N], S_size[M];
  memset(S,0,sizeof(S));
  for(i = 0; i < b; i++){
    S_size[i] = 1<<(i+1);
    for(j = (1<<i)-1; j < (1<<(i+1))-1; j++)
      S[i][j] = S[i][N/2+j] = 1;
  }

  S_size[M-2] = S_size[M-1] = N/2;
  for(i = 0; i < N; i++)
    if(i < N/2) S[M-2][i] = 1;
    else S[M-1][i] = 1;
  
  for(i = 0; i < M; i++) S_cost[i] = 1.0;

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
