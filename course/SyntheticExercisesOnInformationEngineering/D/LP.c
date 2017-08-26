#include <stdio.h>
#include <string.h> // memset
#include <glpk.h>
#include <time.h> // clock

int main(void)
{
  clock_t start = clock();
  int i, j, k, N, M;
  scanf("%d%d", &N, &M);
  int S[M][N];
  memset(S,0,sizeof(S));
  double S_cost[M];
  int S_size[M];
  
  /* 入力を受け取る */
  for(i = 0; i < M; i++){
    scanf("%d%lf", &S_size[i], &S_cost[i]);
    for(j = 0; j < S_size[i]; j++){
      int s;
      scanf("%d", &s);
      S[i][s-1] = 1;
    }
  }

  int f[N], ar_size = 0, f_max = -1;
  memset(f,0,sizeof(f));
  for(i = 0; i < N; i++)
    for(j = 0; j < M; j++)
      if(S[j][i]) f[i]++;

  for(i = 0; i < N; i++){
    if(f_max < f[i]) f_max = f[i];
    ar_size += f[i];
  }
  
  glp_prob *lp;
  int ia[ar_size+1], ja[ar_size+1];
  double ar[ar_size+1], z, x[M];

  lp = glp_create_prob();
  glp_set_obj_dir(lp,GLP_MIN);
  glp_add_cols(lp,M);
  for(i = 1; i <= M; i++){
    glp_set_obj_coef(lp,i,S_cost[i-1]);
    glp_set_col_bnds(lp,i,GLP_DB,0,1);
  }
  glp_add_rows(lp,N);
  for(i = 1; i <= N; i++)
    glp_set_row_bnds(lp,i,GLP_LO,1,0);
  for(i = 0, k = 1; i < N; i++){
    for(j = 0; j < M; j++){
      if(S[j][i]){
        ia[k] = i+1;
        ja[k] = j+1;
        ar[k] = 1;
        k++;
      }
    }
  }
  glp_load_matrix(lp,ar_size,ia,ja,ar);
  glp_simplex(lp,NULL);
  z = glp_get_obj_val(lp);
  for(i = 1; i <= M; i++)
    x[i-1] = glp_get_col_prim(lp,i);

  /* 結果の出力 */
  printf("\nz = %g\n", z);
  for(i = 0; i < M; i++)
    printf("x%d = %lf\n", i+1, x[i]);

  int C[M];
  double total_cost = 0;
  memset(C,0,sizeof(C));
  for(i = 0; i < M; i++){
    if(x[i] >= 1.0/f_max){
      C[i] = 1;
      total_cost += S_cost[i];
    }
  }
  
  printf("\nC = {");
  for(i = 0; i < M; i++)
    if(C[i]) printf(" %d", i+1);
  puts(" }");
  printf("total cost = %lf\n", total_cost);

  clock_t end = clock();
  printf("time = %lf[s]\n", (double)(end-start)/CLOCKS_PER_SEC);
  
  return 0;
}
