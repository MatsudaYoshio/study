#include <iostream>
#include <vector>
#include <queue>
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
    vector<int> level;
    vector<int> iter;

    void bfs(const int s){
        fill_n(begin(this->level), this->v_size, -1);
        
        queue<int> q;
        this->level[s] = 0;
        q.push(s);

        while(!q.empty()){
            const int v = q.front();
            q.pop();

            for(const auto& e : this->g.adj_list[v]){
                if(e.cap > 0 && this->level[e.to] < 0){
                    this->level[e.to] = this->level[v]+1;
                    q.push(e.to);
                }
            }
        }
    }

    int dfs(const int v, const int t, const int f){
        if (v == t) return f;

        for(auto&& e : this->g.adj_list[v]){
            if(e.cap > 0 && this->level[v] < this->level[e.to]){
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

    MaxFlow(const int n):v_size(n), g(n){
        this->level.resize(n);
        this->iter.resize(n);
    }

    int operator()(const int s, const int t){
        int flow = 0;
        while(1){
            this->bfs(s);
            if(this->level[t] < 0) return flow;

            fill_n(begin(this->iter), this->v_size, 0);
            
            int f;
            while((f = this->dfs(s, t, INT_MAX)) > 0) flow += f;
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