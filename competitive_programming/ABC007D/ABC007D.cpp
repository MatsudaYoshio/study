#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

long long int dp[19][2][2];

void set_dp(const int n, const string& num){
    fill(dp[0][0], dp[n+1][0], 0);
    dp[0][0][0] = 1;

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < 2; ++j){
            for(int k = 0; k < 2; ++k){
                int x = j ? 9 : num[i]-'0';
                for(int d = 0; d <= x; ++d){
                    dp[i+1][j || d<x][k || d == 4 || d == 9] += dp[i][j][k];
                }
            }
        }
    }
}

int main(){
    string A, B;
    cin >> A >> B;
    
    const int max_size = B.size();

    long long int ans = 0;
    
    set_dp(max_size, B);
    for(int i = 0; i < 2; ++i) ans += dp[max_size][i][1];

    const string dec_num = to_string(stoll(A)-1);
    const int dec_size = dec_num.size();
    set_dp(dec_size, dec_num);
    for(int i = 0; i < 2; ++i) ans -= dp[dec_size][i][1];

    cout << ans << endl;
}