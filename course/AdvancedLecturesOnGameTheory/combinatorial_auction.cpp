#include <iostream>
#include <array>
#include <vector>
#include <unordered_map>
#include <bitset>
#include <cmath>
#include <climits>

using namespace std;

constexpr int M {3};
constexpr int N {5};

void exhaustive_search(vector<unordered_map<bitset<M>,int>>& v);

int main()
{
  vector<unordered_map<bitset<M>,int>> v(N);
  v[0][bitset<M>("101")] = 40;
  v[0][bitset<M>("110")] = 30;
  v[1][bitset<M>("011")] = 50;
  v[2][bitset<M>("001")] = 30;
  v[2][bitset<M>("101")] = 50;
  v[3][bitset<M>("110")] = 20;
  v[3][bitset<M>("111")] = 60;
  v[4][bitset<M>("100")] = 20;
  v[4][bitset<M>("011")] = 40;
  
  exhaustive_search(v);
}

void exhaustive_search(vector<unordered_map<bitset<M>,int>>& v)
{
  vector<pair<int,bitset<M>>> index_to_v;
  
  for(int i = 0; i < N; ++i){
    for(const auto& s : v[i]){
      index_to_v.emplace_back(make_pair(i,s.first));
    }
  }

  const int n = index_to_v.size();
  
  vector<pair<int,bitset<M>>> opt_i_S;
  int opt_welfare {INT_MIN};
  
  vector<pair<int,bitset<M>>> i_S;
  array<int, M> s_count;
  int w;
  
  for(int b = 0; b < 1<<n; ++b){
    fill(begin(s_count),end(s_count),0);
    i_S.clear();
    w = 0;
    
    for(int i = 0; i < n; ++i){
      if(b & (1<<i)){
        i_S.emplace_back(index_to_v[i]);
        w += v[index_to_v[i].first][index_to_v[i].second];
        
        for(int j = 0; j < M; ++j){
          if(index_to_v[i].second.test(j)){
            ++s_count[j];
          }
        }
      }
    }

    if(any_of(begin(s_count), end(s_count), [](int x) { return x > 1; })){
      continue;
    }

    if(w > opt_welfare){
      opt_welfare = w;
      opt_i_S = move(i_S);
    }
  }

  cout << "The social welfare : " << opt_welfare << endl;
  cout << "-----------------------" << endl;
  for(const auto& e : opt_i_S){
    cout << "bidder " << e.first << " : " << e.second << endl;
  }
  cout << "-----------------------" << endl;
}
