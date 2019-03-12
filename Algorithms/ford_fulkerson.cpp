#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class MaxFlow{
private:
    using Edge = struct edge{
        int to, cap, rev;
        edge(const int to, const int cap, const int rev):to(to), cap(cap), rev(rev){}
    };

    struct Graph{
        vector<vector<Edge>> adj_list;

        Graph(const int v_size){this->adj_list.resize(v_size);}

        void add_edge(const int from, const int to, const int cap){
            this->adj_list[from].emplace_back(Edge{to, cap, static_cast<int>(this->adj_list[to].size())});
            this->adj_list[to].emplace_back(Edge{from, 0, static_cast<int>(this->adj_list[from].size()-1)});
        }
    };

    int v_size;
    vector<bool> used;

    int dfs(const int v, const int t, const int f){
        if (v == t) return f;

        this->used[v] = true;
        for(auto&& e : this->g.adj_list[v]){
            if(!this->used[e.to] && e.cap > 0){
                const int d = this->dfs(e.to, t, min(f, e.cap));
                if(d > 0){
                    e.cap -= d;
                    this->g.adj_list[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }

        return 0;
    }

public:
    Graph g;

    MaxFlow(const int n):v_size(n), g(n){this->used.resize(n);}

    int operator()(const int s, const int t){
        int flow = 0;
        while(1){
            fill_n(begin(this->used), this->v_size, false);
            
            const int f = this->dfs(s, t, INT_MAX);
            if(f == 0) return flow;
            flow += f;
        }
    }
};

int main()
{
    int V, E;
    cin >> V >> E;

    MaxFlow mf(V);
    
    int u, v, c;
    for(int i = 0; i < E; ++i){
        cin >> u >> v >> c;
        mf.g.add_edge(u, v, c);
    }

    cout << mf(0, V-1) << endl;
}