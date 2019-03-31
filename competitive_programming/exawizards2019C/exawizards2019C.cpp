#include <iostream>
#include <string>
#include <vector>
using namespace std;

int N, Q;
string s;
vector<char> t, d;

int C(int x, const bool dir_flag){
    for(int i = 0; i < Q; ++i){
        if(x < 0 || x >= N) break;

        if(s[x] == t[i] && d[i] == 'R') ++x;
        else if(s[x] == t[i] && d[i] == 'L') --x;
    }
    
    if(x < 0) return dir_flag;
    else if(x >= N) return !dir_flag;
    else return false;
}

int main(){
    cin >> N >> Q;
    cin >> s;

    t.resize(Q);
    d.resize(Q);
    for(int i = 0; i < Q; ++i) cin >> t[i] >> d[i];

    int ans = N;

    int lb = -1, ub = N+1, mid;
    while(ub - lb > 1){
        mid = (lb+ub)/2;
        if(C(mid, true)) lb = mid;
        else ub = mid;
    }

    ans -= ub;

    lb = -1;
    ub = N+1;
    while(ub - lb > 1){
        mid = (lb+ub)/2;
        if(C(mid, false)) ub = mid;
        else lb = mid;
    }
    ans -= N-ub;

    cout << ans << endl;
}