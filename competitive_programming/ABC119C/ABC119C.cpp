#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, A, B, C;
vector<int> l;

int dfs(int d, int a, int b, int c){
    if(d == N){
        if(min({a, b, c}) > 0){
            return abs(a-A)+abs(b-B)+abs(c-C)-30;
        }else{
            return 10000000;   
        }
    }else{
        return min({
            dfs(d+1, a+l[d], b, c)+10,
            dfs(d+1, a, b+l[d], c)+10,
            dfs(d+1, a, b, c+l[d])+10, 
            dfs(d+1, a, b, c)
            });
    }
}

int main(){
    cin >> N >> A >> B >> C;

    l.resize(N);
    for(int i = 0; i < N; ++i){
        cin >> l[i];
    }

    cout << dfs(0, 0, 0, 0) << endl;
}