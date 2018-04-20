#include <iostream>
#include <vector>

using namespace std;

bool is_subset_sum(const vector<int>& a, const int k){
  auto n {a.size()};
  bool dp[n+1][k+1];
  memset(dp, false, sizeof(dp));
  dp[0][0] = true;

  for(int i = 0; i < n; ++i){
    for(int j = 0; j <= k; ++j){
      dp[i+1][j] |= dp[i][j];
      if(j >= a[i]) dp[i+1][j] |= dp[i][j-a[i]];
    }
  }

  return dp[n][k];
}

int main()
{
  vector<int> a {1, 2, 4, 7};
  int k {13};

  cout << (is_subset_sum(a, k) ? "YES" : "NO") << endl;
}
