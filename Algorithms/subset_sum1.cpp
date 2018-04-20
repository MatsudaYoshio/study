#include <iostream>
#include <vector>

using namespace std;

bool is_subset_sum(const vector<int>& a, const int i, const int sum, const int k){
  if(i == a.size()) return sum == k;

  if(is_subset_sum(a, i+1, sum, k)) return true;

  if(is_subset_sum(a, i+1, sum+a[i], k)) return true;

  return false;
}

int main()
{
  vector<int> a {1, 2, 4, 7};
  int k {15};

  cout << (is_subset_sum(a, 0, 0, k) ? "YES" : "NO") << endl;
}
