#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
using namespace std;

using pii = pair<int, int>;

int main(){
    int N, M;
    cin >> N >> M;
    
    vector<pii> AB(N);
    for(int i = 0; i < N; ++i){
        cin >> AB[i].first >> AB[i].second;
    }

    sort(begin(AB), end(AB));

    priority_queue<pii, vector<pii>, function<bool(pii, pii)>> q(
        [](const pii& a, const pii& b){
            return (a.second == b.second) ? (a.first > b.first) : (a.second < b.second);
        }
    );

    int ans = 0;
    int d = 0;
    int j = 0;
    while(d <= M && j <= N){
        if(!q.empty()){
            ans += q.top().second;
            q.pop();
        }
        
        ++d;
        for(int i = j; i < N; ++i){
            if(AB[i].first == d){
                q.emplace(AB[i]);
                ++j;
            }else{
                break;
            }
        }
    }

    cout << ans << endl;
}