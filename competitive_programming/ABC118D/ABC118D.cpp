#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

constexpr int match_num[] = {-1, 2, 5, 5, 4, 5, 6, 3, 7, 6};

int main(){
    int N, M;
    cin >> N >> M;

    vector<int> A(M);
    for(int i = 0; i < M; ++i){
        cin >> A[i];
    }

    vector<int> dp(N+1, 0);
    for(int i = 1; i <= N; ++i){
        for(int j = 0; j < M; ++j){
            if(i-match_num[A[j]] >= 0){
                dp[i] = max(dp[i], dp[i-match_num[A[j]]]+1);
            }
        }

        if(dp[i] == 0){
            dp[i] = -1;
        }
    }

    sort(begin(A), end(A), greater<int>());

    string ans = "";
    while(N > 0){
        for(int i = 0; i < M; ++i){
            if(N-match_num[A[i]] >= 0 && dp[N-match_num[A[i]]] == dp[N]-1){
                ans += to_string(A[i]);
                N -= match_num[A[i]];
                break;
            }
        }
    }

    cout << ans << endl;
}