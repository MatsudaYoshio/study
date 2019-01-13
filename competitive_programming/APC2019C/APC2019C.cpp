#include <iostream>
#include <queue>
#include <vector>
using namespace std;

using pxy =  pair<int, int>;
const int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};

int main()
{
  int H, W;
  cin >> H >> W;

  vector<vector<bool>> used = vector<vector<bool>>(H, vector<bool>(W, false));
  
  vector<string> m(H);
  for(int i = 0; i < H; ++i) cin >> m[i];
  
  int x, y;
  long long int b, w;
  queue<pxy> q;
  long long int ans = 0;
  for(int i = 0; i < H; ++i){
    for(int j = 0; j < W; ++j){
      if(used[i][j]) continue;
      
      b = w = 0;
      q.push(pxy(i, j));
      used[i][j] = true;
      
      while(!q.empty()){     
        x = q.front().first;
        y = q.front().second;
        
        q.pop();
        
        if(m[x][y] == '#') ++b;
        else ++w;
        
        for(int k = 0; k < 4; ++k){
          int next_x = x + dx[k], next_y = y + dy[k];
          if(next_x < 0 || next_x >= H || next_y < 0 || next_y >= W || m[next_x][next_y] == m[x][y] || used[next_x][next_y]) continue;
          q.push(pxy(next_x, next_y));
          used[next_x][next_y] = true;
        }
      }
      ans += b*w;
    }
  }

  cout << ans << endl;
}
