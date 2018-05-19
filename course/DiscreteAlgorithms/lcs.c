#include <stdio.h>
#include <string.h>

enum Direction {DIAGONAL, VERTICAL, HORIZONTAL};

void lcs(const char* x, const char* y){
  int i, j, k;
  
  int m = strlen(x);
  int n = strlen(y);
  
  int dp[m+1][n+1], t[m+1][n+1];
  for(i = 0; i <= m; ++i) dp[i][0] = 0;
  for(i = 1; i <= n; ++i) dp[0][i] = 0;
  
  for(i = 0; i < m; ++i){
    for(j = 0; j < n; ++j){
      if(x[i] == y[j]){
        dp[i+1][j+1] = dp[i][j]+1;
        t[i+1][j+1] = DIAGONAL;
      }else if(dp[i+1][j] > dp[i][j+1]){
        dp[i+1][j+1] = dp[i+1][j];
        t[i+1][j+1] = VERTICAL;
      }else{
        dp[i+1][j+1] = dp[i][j+1];
        t[i+1][j+1] = HORIZONTAL;
      }
    }
  }

  int lcs_size = dp[m][n];
  char lcs[lcs_size+1];
  lcs[lcs_size] = '\0';

  i = m;
  j = n;
  k = lcs_size;
  while(i != 0 && j != 0){
    switch(t[i][j]){
    case DIAGONAL:
      lcs[--k] = x[i-1];
      --i;
      --j;
      break;
    case VERTICAL:
      --j;
      break;
    case HORIZONTAL:
      --i;
      break;
    }
  }
  
  printf("%d(\"%s\")\n", lcs_size, lcs);
} 

int main()
{
  lcs("aabacbab", "cbcacabca");
}
