#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int N, M;
    cin >> N >> M;

    bool adj[N][N];
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            adj[i][j] = (i == j) ? true : false;
        }
    }

    for(int i = 0, x, y; i < M; ++i){
        cin >> x >> y;
        adj[x-1][y-1] = adj[y-1][x-1] = true;
    }

    int ans = 1;
    bool g[N];
    for(int b = 0; b < 1<<N; ++b){
        fill_n(g, N, false);
        for(int i = 0; i < N; ++i){
            if(b & (1<<i)){
                g[i] = true;
            }
        }

        for(int i = 0; i < N; ++i){
            if(g[i]){
                for(int j = 0; j < N; ++j){
                    if(g[j] && !adj[i][j]){
                        goto FAIL;
                    }
                }
            }
        }

        ans = max(ans, static_cast<int>(count(g, g+N, true)));
        FAIL:;
    }

    cout << ans << endl;
}