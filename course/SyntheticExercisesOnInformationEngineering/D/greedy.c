#include <stdio.h>
#include <string.h> // memset
#include <float.h> // DBL_MAX
#include <time.h> // clock

int isCover(int a[], int n)
{ // 配列が全て1かどうかチェックする
  int i;
  for(i = 0; i < n; i++) if(!a[i]) return 0;
  return 1;
}

int main(void)
{
  clock_t start = clock();
  int i, j, N, M;
  scanf("%d%d", &N, &M);
  double S_cost[M];
  int S[M][N], S_size[M], Sum[N], C[M];
  memset(S,0,sizeof(S));
  memset(Sum,0,sizeof(Sum));
  memset(C,0,sizeof(C));
  double total_cost = 0;
  
  /* 入力を受け取る */
  for(i = 0; i < M; i++){
    scanf("%d%lf", &S_size[i], &S_cost[i]);
    for(j = 0; j < S_size[i]; j++){
      int s;
      scanf("%d", &s);
      S[i][s-1] = 1;
    }
  }
  
  while(!isCover(Sum, N)){ // 全てを被覆するまで繰り返す
    
    /* 最小の単価となるmin_Sを求める */
    double min_cost = DBL_MAX;
    int min_S;
    for(i = 0; i < M; i++){
      if(S_size[i] != 0 && S_cost[i]/S_size[i] < min_cost){
        min_cost = S_cost[i]/S_size[i];
        min_S = i;
      }
    }
    
    C[min_S] = 1; // 選択したmin_Sを結果表示の集合に追加する
    total_cost += S_cost[min_S]; // 選択したmin_Sのコストを加える

    /* min_Sの要素を被覆して，それを他のSから除外する */
    for(i = 0; i < N; i++){
      if(S[min_S][i]){
        Sum[i] = 1;
        for(j = 0; j < M; j++){
          if(j != min_S && S_size[j] != 0 && S[j][i]){
            S_size[j]--;
            S[j][i] = 0;
          }
        }
      }
    }
    S_size[min_S] = 0; // 選んだmin_Sは二度と選ばれないようにする
  }

  /* 結果の出力 */
  printf("C = {");
  for(i = 0; i < M; i++)
    if(C[i]) printf(" %d", i+1);
  puts(" }");
  printf("total cost = %lf\n", total_cost);

  clock_t end = clock();
  printf("time = %lf[s]\n", (double)(end-start)/CLOCKS_PER_SEC);
  
  return 0;
}
