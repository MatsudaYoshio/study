#include <climits>
#include <iostream>
#include <unordered_set>
#include <queue>
#include <algorithm>

using namespace std;

constexpr int NIL {-1};

void MAXWM4BG(const vector<int>& X, const vector<int>& Y, vector<unordered_set<int>>& gamma_G, const vector<vector<int>>& w);
void SEARCH(const int x, const vector<int>& X, const vector<int>& Y, vector<unordered_set<int>>& gamma_G, vector<unordered_set<int>>& gamma_H, vector<int>& match, const vector<vector<int>>& w, vector<int>& y);

int main()
{
  const vector<int> X { 0, 1, 2, 3, 4 };
  const vector<int> Y { 5, 6, 7, 8, 9 };
  const vector<vector<int>> w {
    { 3, 1, 1, 1, 0 },
    { 2, 0, 0, 2, 7 },
    { 3, 0, 0, 1, 0 },
    { 4, 0, 5, 0, 1 },
    { 0, 2, 1, 0, 1 }
  };

  vector<unordered_set<int>> gamma_G(X.size());
  for(int i = 0; i < w.size(); ++i){
    for(int j = 0; j < w[i].size(); ++j){
      if(w[i][j] != 0){
        gamma_G[X[i]].emplace(Y[j]);
      }
    }
  }
  
  MAXWM4BG(X, Y, gamma_G, w);
}

void MAXWM4BG(const vector<int>& X, const vector<int>& Y, vector<unordered_set<int>>& gamma_G, const vector<vector<int>>& w)
{
  vector<int> y(X.size()+Y.size(), 0);
  vector<int> match(X.size()+Y.size(), NIL);
  vector<unordered_set<int>> gamma_H(X.size());
  
  for(const auto& u : X){
    y[u] = *max_element(begin(w[u]), end(w[u]));
    
    for(const auto& v : gamma_G[u]){
      if(y[u] + y[v] == w[u][v-Y.size()]){
        gamma_G[u].erase(v);
        gamma_H[u].emplace(v);
      }
    }
  }
  
  for(const auto& u : X){
    if(y[u] > 0){
      SEARCH(u, X, Y, gamma_G, gamma_H, match, w, y);
    }
  }
  
  for(const auto& u : X){
    if(match[u] == NIL) continue;
    
    cout << u << " " << match[u] << endl;
  }
}

void SEARCH(const int x, const vector<int>& X, const vector<int>& Y, vector<unordered_set<int>>& gamma_G, vector<unordered_set<int>>& gamma_H, vector<int>& match, const vector<vector<int>>& w, vector<int>& y)
{
  constexpr bool YES {true};
  constexpr bool NO {false};
  constexpr int augment {-2};
  constexpr int modify {-3};
  
  queue<int> Q;
  vector<bool> visit(X.size(),NO);
  vector<int> parent(X.size()+Y.size(),NIL);
  int flag, endv;
  
  Q.push(x);
  visit[x] = YES;
  flag = NIL;

  while(y[x] != 0 && flag == NIL){
    while(!Q.empty()){
      int u {Q.front()}; Q.pop();
      for(const auto& v : gamma_H[u]){
        if(match[v] == NIL){
          parent[v] = u;
          endv = v;
          flag = augment;
          queue<int>().swap(Q);
          break;
        }else{
          int z {match[v]};
          if(visit[z] == NO){
            parent[v] = u;
            Q.push(z);
            visit[z] = YES;
            if(y[z] == 0){
              endv = z;
              flag = modify;
              queue<int>().swap(Q);
              break;
            }
          }
        }
      }
    }
    
    if(flag == NIL){
      int delta1 {INT_MAX};
      for(const auto& u : X){
        if(visit[u] == YES){
          delta1 = min(delta1, y[u]);
        }
      }
      
      int delta2 {INT_MAX};
      for(const auto& u : X){
        if(visit[u] == YES){
          for(const auto& v : gamma_G[u]){
            if(match[v] == NIL || visit[match[v]] == NO){
              delta2 = min(delta2, y[u]+y[v]-w[u][v-Y.size()]);
            }
          }
        }
      }
      
      int delta {min(delta1,delta2)};

      for(const auto& u : X){
        if(visit[u] == NO) continue;

        y[u] -= delta;

        for(const auto& v : gamma_G[u]){
          if(match[v] != NIL && visit[match[v]] == YES) continue;

          if(y[u] + y[v] == w[u][v-Y.size()]){
            gamma_G[u].erase(v);
            gamma_H[u].emplace(v);
            if(flag == NIL){
              parent[v] = u;
              if(match[v] == NIL){
                endv = v;
                flag = augment;
                queue<int>().swap(Q);
              }else{
                int z {match[v]};
                Q.push(z);
                visit[z] = YES;
              }
            }
          }
        }
        
        if(u != x){
          y[match[u]] += delta;
        }
      }

      for(const auto& u : X){
        if(visit[u] == YES) continue;

        for(const auto& v : gamma_H[u]){
          if(match[v] != NIL && visit[match[v]] == YES){
            gamma_H[u].erase(v);
            gamma_G[u].emplace(v);
          }
        }
      }
    }
  }

  if(flag != NIL){
    if(flag == modify){
      int v {match[endv]};
      match[endv] = NIL;
      endv = v;
    }
    
    while(parent[endv] != x){
      int u {parent[endv]};
      int v {match[u]};
      match[endv] = u;
      match[u] = endv;
      endv = v;
    }
    
    match[endv] = x;
    match[x] = endv;
  }
}
