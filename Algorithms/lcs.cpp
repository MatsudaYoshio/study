#include <iostream>
#include <string>
#include <algorithm>
#include <cstdio>

using namespace std;

enum Direction {DIAGONAL, VERTICAL, HORIZONTAL};

void lcs(const string& x, const string& y){
  auto m {x.size()};
  auto n {y.size()};

  int dp[m+1][n+1], t[m+1][n+1];
  fill(dp[0], dp[m+1], 0);
  
  for(int i = 0; i < m; ++i){
    for(int j = 0; j < n; ++j){
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
  
  string lcs(dp[m][n], '\0');
  for(int i = m, j = n, k = dp[m][n]; k > 0;){
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

  printf("%d(\"%s\")\n", dp[m][n], lcs.c_str());
} 

int main()
{
  lcs("abcbdab", "bdcaba");
}
