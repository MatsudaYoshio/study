#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdio>
using namespace std;

int main()
{
  int N, M;
  scanf("%d%d", &N, &M);

  vector<int> A(N+1), B(M+1);
  const int MAX_N = N*M;
  constexpr long long int MOD = 1000000007;
  for(int i = 0; i < N; ++i) scanf("%d", &A[i]);
  for(int j = 0; j < M; ++j) scanf("%d", &B[j]);

  sort(begin(A), end(A), greater<int>());
  sort(begin(B), end(B), greater<int>());
  
  long long int ba = 0, bb = 0;
  long long int ans = 1;
  for(long long int i = MAX_N; i > 0; --i){
    if(A[ba] == i && B[bb] == i){
      ++ba, ++bb;
    }else if(A[ba] == i && B[bb] != i){
      ++ba;
      ans = (ans*bb) % MOD;
    }else if(A[ba] != i && B[bb] == i){
      ++bb;
      ans = (ans*ba) % MOD;
    }else{
      ans = (ans*(ba*bb-MAX_N+i)) % MOD;
    }

    if(ans <= 0){
      ans = 0;
      break;
    }
  }

  cout << ans << endl;
}
