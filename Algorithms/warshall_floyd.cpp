#include <iostream>
#include <vector>

using namespace std;

constexpr int INF {INT_MAX >> 1};

struct Graph{
  int v_size;
  vector<vector<int>> d;
  
  Graph(const int v_size):v_size(v_size){
    this->d = vector<vector<int>>(v_size, vector<int>(v_size, INF));
    for(int i = 0; i < v_size; ++i) d[i][i] = 0;
  }
  
  void add_edge(const int s, const int t, const int w){
    this->d[s][t] = w;
  }
};

void warshall_floyd(Graph& g){
  for(int i = 0; i < g.v_size; ++i){
    for(int j = 0; j < g.v_size; ++j){
      for(int k = 0; k < g.v_size; ++k){
        g.d[j][k] = min(g.d[j][k], g.d[j][i] + g.d[i][k]);
      }
    }
  }

  for(int i = 0; i < g.v_size; ++i){
    if(g.d[i][i] < 0){
      cout << "Detect negative cycle!!" << endl;
      return;
    }
  }
  
  for(int i = 0; i < g.v_size; ++i){
    for(int j = 0; j < g.v_size; ++j){
      if(i != j && g.d[i][j] != INF){
        cout << i << " -> " << j << " : " << g.d[i][j] << endl;
      }
    }
  }
}

int main()
{
  int n;
  cin >> n;
  
  Graph g(n);

  int u, k, v, c;
  for(int i = 0; i < n; ++i){
    cin >> u >> k;
    for(int j = 0; j < k; ++j){
      cin >> v >> c;
      g.add_edge(u, v, c);
    }
  }

  warshall_floyd(g);
}
