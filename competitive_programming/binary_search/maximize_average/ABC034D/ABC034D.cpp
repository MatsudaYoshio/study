#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
#include <cstdio>
using namespace std;

int N, K;
vector<int> w, p;
vector<double> y;

bool C(double x)
{
  y.resize(N);
  for(int i = 0; i < N; ++i){
    y[i] = (p[i]-100*x)*w[i]/100.0;
  }
  sort(begin(y), end(y), greater<double>());
  
  return accumulate(begin(y), begin(y)+K, 0.0) >= 0;
}

int main()
{
  scanf("%d%d", &N, &K);

  w.resize(N);
  p.resize(N);
  
  for(int i = 0; i < N; ++i) scanf("%d%d", &w[i], &p[i]);
  
  double lb = 0, ub = 1;
  for(int i = 0; i < 50; ++i){
    double mid = (lb+ub)/2;
    if(C(mid)) lb = mid;
    else ub = mid;
  }

  printf("%.9lf\n", ub*100);
}
