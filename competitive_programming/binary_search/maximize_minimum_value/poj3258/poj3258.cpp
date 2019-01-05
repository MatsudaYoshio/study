#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int L, N, M;
vector<int> r;

bool C(int d)
{
  int prev, crt = 0, cnt;
  int m = M;
  while(crt <= N+1){
    ++crt;
    prev = crt-1;

    cnt = 0;
    while(crt <= N+1 && r[crt]-r[prev] < d){
      ++crt;
      ++cnt;
    }
    
    m -= cnt;

    if(m < 0) return false;
  }
  return true;
}

int main()
{
  cin >> L >> N >> M;
  r.resize(N+2);
  r[0] = 0;
  for(int i = 1; i <= N; ++i) cin >> r[i];
  r[N+1] = L;

  sort(r.begin(), r.end());

  int lb = 0, ub = 1000000000, mid;
  
  while(ub - lb > 1){
    mid = (lb + ub)/2;
    if(C(mid)) lb = mid;
    else ub = mid;
  }

  cout << lb << endl;
}
