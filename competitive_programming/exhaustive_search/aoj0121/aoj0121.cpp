#include <iostream>
#include <cstdio>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

using Data = struct{
    int pos;
    string puzzle;
    int t;
};

constexpr int dx[] = {-1, 1, -4, 4};
const string correct{"01234567"};

int main(){
    map<string, int> min_root{{correct, 0}};
    
    queue<Data> q;
    q.push(Data{0, correct, 0});
    while(!q.empty()){
        Data d = q.front();
        q.pop();

        for(int i = 0; i < 4; ++i){
            int npos = d.pos+dx[i];

            if(npos < 0 || npos > 7 || (d.pos == 3 && npos == 4) || (d.pos == 4 && npos == 3)) continue;

            string npuzzle = d.puzzle;
            swap(npuzzle[d.pos], npuzzle[npos]);

            if(min_root.find(npuzzle) != end(min_root)) continue;

            min_root.emplace(make_pair(npuzzle, d.t+1));
            q.push(Data{npos, npuzzle, d.t+1});
        }
    }

    cin.tie(0);
    ios::sync_with_stdio(false);

    string puzzle(8, ' ');

    while (cin >> puzzle[0] >> puzzle[1] >> puzzle[2] >> puzzle[3] >> puzzle[4] >> puzzle[5] >> puzzle[6] >> puzzle[7]) {
        cout << min_root[puzzle] << endl;
    }
}