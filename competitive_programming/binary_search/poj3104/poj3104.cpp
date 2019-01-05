#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
using namespace std;

int n, k;
vector<int> a;

bool C(int t)
{
  int cnt = t;
  for(int i = 0; i < n; ++i){
    if(a[i] > t){
      cnt -= ceil((double)(a[i]-t) / (k-1));
      if(cnt < 0) return false;
    }
  }

  return true;
}

int main()
{
  scanf("%d", &n);

  a.resize(n);
  for(int i = 0; i < n; ++i) scanf("%d", &a[i]);

  scanf("%d", &k);

  int lb = 0, ub = 1000000000, mid;

  while(ub - lb > 1){
    mid = (lb + ub)/2;
    if(C(mid)) ub = mid;
    else lb = mid;
  }

  cout << ub << endl;
}
