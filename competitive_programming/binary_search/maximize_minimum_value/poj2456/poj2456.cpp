#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M;
vector<int> x;

bool C(int d)
{
  int prev = 0, crt;
  for(int i = 1; i < M; ++i){
    crt = prev+1;
    while(crt < N && x[crt] - x[prev] < d){
      ++crt;
    }
    if(crt == N) return false;
    prev = crt;
  }

  return true;
}

int main()
{
  cin >> N >> M;
  x.resize(N);
  for(int i = 0; i < N; ++i) cin >> x[i];

  sort(x.begin(), x.end());

  int lb = 0, ub = 1000000000, mid;
  while(ub - lb > 1){
    mid = (lb+ub)/2;
    if(C(mid)) lb = mid;
    else ub = mid;
  }

  cout << lb << endl;
}
