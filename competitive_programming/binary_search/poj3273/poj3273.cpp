#include <iostream>
#include <vector>
using namespace std;

int N, M;
vector<int> E;

bool C(int e)
{
  int sum;
  int m = M;
  for(int i = 0; i < N;){

    sum = 0;
    while(1){
      sum += E[i++];
      if(sum > e){
        --i;
        --m;
        break;
      }else if(i == N){
        --m;
        break;
      }
    }

    if(m < 0) return false;
    
  }
  return true;
}

int main()
{
  cin >> N >> M;
  E.resize(N);

  for(int i = 0; i < N; ++i) cin >> E[i];

  int lb = 0, ub = 1000000000, mid;

  while(ub - lb > 1){
    mid = (lb + ub)/2;
    if(C(mid)) ub = mid;
    else lb = mid;
  }

  cout << ub << endl;
}
