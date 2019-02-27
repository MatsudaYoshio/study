#include <vector>
#include <queue>
#include <algorithm>
#include <cstdio>
#include <climits>
using namespace std;

typedef struct{int x, y;} Point;
typedef struct{
    Point p;
    int t; 
} Data;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, 1, -1};
const int MAX_X = 303;
const int MAX_Y = 303;

int main(){
    int M;
    scanf("%d", &M);

    vector<vector<int> > m(MAX_X, vector<int>(MAX_Y, INT_MAX));
    for(int i = 0, X, Y, T; i < M; ++i){
        scanf("%d%d%d", &X, &Y, &T);

        m[X][Y] = min(m[X][Y], T);
        for(int j = 0, nx, ny; j < 4; ++j){
            nx = X+dx[j];
            ny = Y+dy[j];

            if(nx < 0 || nx > MAX_X || ny < 0 || ny > MAX_Y) continue;

            m[nx][ny] = min(m[nx][ny], T);
        }
    }

    vector<vector<bool> > visited(MAX_X, vector<bool>(MAX_Y, false));
    visited[0][0] = true;
    queue<Data> q;
    q.push(Data{Point{0, 0}, 0});
    while(!q.empty()){
        Data d = q.front();
        q.pop();

        if(m[d.p.x][d.p.y] == INT_MAX){
            printf("%d\n", d.t);
            return 0;
        }

        for(int i = 0, nx, ny; i < 4; ++i){
            nx = d.p.x+dx[i];
            ny = d.p.y+dy[i];

            if(nx < 0 || nx > MAX_X || ny < 0 || ny > MAX_Y || visited[nx][ny] || d.t+1 >= m[nx][ny]) continue;

            visited[nx][ny] = true;

            q.push(Data{Point{nx, ny}, d.t+1});
        }
    }

    puts("-1");
}