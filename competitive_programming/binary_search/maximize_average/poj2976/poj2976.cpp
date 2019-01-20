#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>
using namespace std;

int n, k;
vector<int> a, b;
vector<double> y;

bool C(double x)
{
  y.resize(n);
  for(int i = 0; i < n; ++i){
    y[i] = a[i] - x*b[i];
  }
  sort(y.begin(), y.end(), greater<double>());
  
  double sum = 0;
  for(int i = 0; i < n - k; ++i){
    sum += y[i];
  }

  return sum >= 0;
}

int main()
{
  while(1){
    cin >> n >> k;
    if(n == 0 && k == 0) break;

    a.resize(n);
    for(int i = 0; i < n; ++i) cin >> a[i];
    
    b.resize(n);
    for(int i = 0; i < n; ++i) cin >> b[i];

    double lb = 0, ub = 1;
    for(int i = 0; i < 100; ++i){
      double mid = (lb+ub)/2;
      if(C(mid)) lb = mid;
      else ub = mid;
    }

    cout << round(ub*100) << endl;
  }
}
