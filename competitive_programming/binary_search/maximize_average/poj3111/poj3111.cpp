#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>
#include <cstdio>
using namespace std;

int n, k;
vector<int> v, w;
vector<pair<double, int> > y;

bool C(double x)
{
  y.resize(n);
  for(int i = 0; i < n; ++i){
    y[i].first = v[i] - x*w[i];
    y[i].second = i+1;
  }
  sort(y.begin(), y.end(), greater<pair<double, int> >());
  
  double sum = 0;
  for(int i = 0; i < k; ++i){
    sum += y[i].first;
  }

  return sum >= 0;
}

int main()
{
  scanf("%d%d", &n, &k);

  v.resize(n);
  w.resize(n);
  
  for(int i = 0; i < n; ++i) scanf("%d%d", &v[i], &w[i]);
  
  double lb = 0, ub = 100000000;
  for(int i = 0; i < 50; ++i){
    double mid = (lb+ub)/2;
    if(C(mid)) lb = mid;
    else ub = mid;
  }

  printf("%d", y[0].second);
  for(int i = 1; i < k; ++i) printf(" %d", y[i].second);
  putchar('\n');
}
