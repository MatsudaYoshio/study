#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

using pii = pair<int, int>;

int N;
vector<pii> index2pos;
vector<vector<int>> dp;
vector<int> X, Y;

int dfs(const int dl, const int ur, map<pii, int>& m){
    int& ret = dp[dl][ur];
    if (ret >= 0) return ret;
    ret = 0;
    
    const int x0 = index2pos[dl].first, y0 = index2pos[dl].second;
    const int x1 = index2pos[ur].first, y1 = index2pos[ur].second;
    
    for (int i = 1; i < N-1; ++i){
        if (x0 < X[i] && X[i] < x1 && y0 < Y[i] && Y[i] < y1){
            int sum = (x1-x0-1) + (y1-y0-1) - 1;

            sum += dfs(dl, m[pii(X[i], Y[i])], m);
            sum += dfs(m[pii(x0, Y[i])], m[pii(X[i], y1)], m);
            sum += dfs(m[pii(X[i], y0)], m[pii(x1, Y[i])], m);
            sum += dfs(m[pii(X[i], Y[i])], ur, m);

            ret = max(ret, sum);
        }
    }

    return ret;
}

int main(){
    int W, H;
    scanf("%d%d%d", &W, &H, &N);

    X.resize(N+2, W+1);
    Y.resize(N+2, H+1);
    for(int i = 1; i <= N; ++i) scanf("%d%d", &X[i], &Y[i]);
    X[0] = Y[0] = 0;

    N += 2;

    const int max_size = N*N+2;

    map<pii, int> m;
    for (int i = 0; i < N; ++i){
        m.emplace(pii(X[i], Y[i]), 0);
        for (int j = i+1; j < N; ++j) {
            m.emplace(pii(X[i], Y[j]), 0);
            m.emplace(pii(X[j], Y[i]), 0);
        }
    }

    index2pos.resize(max_size);
    int k = 0;
    for (auto&& p : m){
        p.second = k;
        index2pos[k++] = p.first;
    }

    dp.resize(max_size);
    for(int i = 0; i < max_size; ++i) dp[i].resize(max_size, -1);

    printf("%d\n", dfs(m[pii(0, 0)], m[pii(W+1, H+1)], m));
}