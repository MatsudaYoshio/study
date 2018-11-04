#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Graph{
  int v_size;
  vector<vector<int>> adj;

  Graph(const int v_size):v_size(v_size){
    this->adj.resize(v_size);
  }

  void add_edge(const int s, const int t){
    this->adj[s].emplace_back(t);
  }
};

void tsort(const Graph& g)
{
  vector<int> indeg(g.v_size);
  for(const auto& u : g.adj){
    for(const auto& to : u){
      ++indeg[to];
    }
  }
  
  vector<bool> used(g.v_size);
  queue<int> q;

  vector<int> ans;
  ans.reserve(g.v_size);
  
  for(int i = 0; i < g.v_size; ++i){
    if(indeg[i] == 0 && !used[i]){
      q.push(i);
      used[i] = true;

      while(!q.empty()){
        auto u {q.front()};
        q.pop();
        
        ans.emplace_back(u);

        for(const auto& v : g.adj[u]){
          --indeg[v];

          if(indeg[v] == 0 && !used[v]){
            q.push(v);
            used[v] = true;
          }
        }        
      }
    }
  }

  if(ans.size() != g.v_size){
    cout << "There is a cycle in this graph" << endl;
  }
  
  for(const auto& v : ans){
    cout << v << endl;
  }
}

int main()
{
  int V, E;
  cin >> V >> E;

  Graph g(V);

  int s, t;
  for(int i = 0; i < E; ++i){
    cin >> s >> t;
    g.add_edge(s,t);
  }

  tsort(g);
}
