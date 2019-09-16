#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void z_algorithm(const string& s, vector<int>& Z){
    const int n = s.size();
    Z = vector<int>(n, 0);
    for(int i = 1, j = 0; i < n; ++i){
        if(i+Z[i-j] < j+Z[j]){
            Z[i] = Z[i-j];
        }else{
            auto k = max(0, j+Z[j]-i);
            while(i+k < n && s[k] == s[i+k]) ++k;
            Z[i] = k;
            j = i;
        }
    }
    Z[0] = n;
}

int main(){
    int N;
    cin >> N;

    string S;
    cin >> S;

    vector<vector<int>> dp(N, vector<int>(N, 0));
    for(int i = 0; i < N; ++i){
        vector<int> Z;
        z_algorithm(S.substr(i), Z);
        copy(begin(Z), end(Z), &dp[i][i]);
    }

    int ans = 0;
    for(int i = 0; i < N; ++i){
        for(int j = i+1; j < N; ++j){
            ans = max(min(j-i, dp[i][j]), ans);
        }
    }

    cout << ans << endl;
}