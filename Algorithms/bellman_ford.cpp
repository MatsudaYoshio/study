#include <iostream>
#include <vector>

using namespace std;

struct Edge{
  int to, cost;
  Edge(const int to, const int cost):to(to),cost(cost){}
};

struct Graph{
  int v_size;
  vector<vector<Edge>> edge;
  
  Graph(const int v_size):v_size(v_size){
    this->edge.resize(v_size);
  }
  
  void add_edge(const int s, const int t, const int w){
    this->edge[s].emplace_back(Edge{t, w});
  }
};

void bellman_ford(const Graph& g, const int s, const int t){
  vector<int> prev(g.v_size, g.v_size);
  
  constexpr int INF {INT_MAX};
  vector<int> d(g.v_size, INF);
  d[s] = 0;

  for(int i = 0; i < g.v_size; ++i){
    for(int v = 0; v < g.v_size; ++v){
      for(int k = 0; k < g.edge[v].size(); ++k){
        Edge e {g.edge[v][k]};
        if(d[v] != INF && d[e.to] > d[v] + e.cost){
          if(i == g.v_size - 1){
            cout << "Detect negative cycle!!" << endl;
            return;
          }
          
          d[e.to] = d[v] + e.cost;
          prev[e.to] = v;
        }
      }
    }
  }

  vector<int> path;
  for(int i = t; prev[i] != g.v_size; i = prev[i]){
    path.emplace_back(i);
  }

  reverse(begin(path), end(path));
  
  cout << d[t] << "(" << s;
  for(const auto& v : path){
    cout << " -> " << v;
  }
  cout << ")" << endl;
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

  bellman_ford(g, 0, 4);
}
