#include <iostream>
#include <queue>

using namespace std;

using pii = pair<int, int>;

struct Graph{
  int v_size;
  vector<vector<pii>> adj;
  
  Graph(const int v_size):v_size(v_size){
    this->adj.resize(v_size);
  }
  
  void add_edge(const int s, const int t, const int w){
    this->adj[s].emplace_back(pii(t, w));
  }
};

void dijkstra(const Graph& g, const int s, const int t){
  vector<int> prev(g.v_size, g.v_size);
  
  constexpr int INF {INT_MAX};
  enum {UNCHECKED, CHECKED, INCLUDE};
  priority_queue<pii, vector<pii>, greater<pii>> pq;
  vector<int> d(g.v_size, INF);
  vector<int> state(g.v_size, UNCHECKED);
  
  d[s] = 0;
  pq.push(pii(0, s));
  state[s] = INCLUDE;

  pii f;
  int v;
  while(!pq.empty()){
    f = pq.top();
    pq.pop();
    state[f.second] = CHECKED;

    if(d[f.second] < f.first) continue;

    for(int i = 0; i < g.adj[f.second].size(); ++i){
      v = g.adj[f.second][i].first;
      if(state[v] == CHECKED) continue;
      if(d[v] > d[f.second] + g.adj[f.second][i].second){
        d[v] = d[f.second] + g.adj[f.second][i].second;
        pq.push(pii(d[v], v));
        state[v] = INCLUDE;

        prev[v] = f.second;
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

  dijkstra(g, 0, 4);
}
