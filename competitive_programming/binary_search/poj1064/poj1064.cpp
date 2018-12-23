#include <iostream>
#include <cmath>
#include <vector>
#include <cstdio>
using namespace std;

int N, K;
vector<double> L;

bool C(double x)
{
  int sum = 0;
  for(int i = 0; i < N; ++i){
    sum += floor(L[i]/x);
  }
  return sum >= K;
}

int main()
{
  cin >> N >> K;

  L.resize(N);
  for(int i = 0; i < N; ++i) cin >> L[i];

  double lb = 0, ub = 100000;
  double mid;
  for(int i = 0; i < 100; ++i){
    mid = (lb+ub)/2;
    if(C(mid)) lb = mid;
    else ub = mid;
  }

  printf("%.2lf\n", floor(ub*100)/100);
}
