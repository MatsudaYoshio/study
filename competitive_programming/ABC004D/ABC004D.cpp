#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main(){
    int R, G, B;
    cin >> R >> G >> B;

    vector<int> cost(600, 0);
    for(int i = 1; i < 600; ++i){
        cost[i] = i+cost[i-1];
        cout << cost[i] << endl;
    }

    int ans = INT_MAX;
    int r, b, m;
    for(int g = -299; g <= 299; ++g){
        m = 0;

        r = min(g-R, -100-R/2);
        b = max(g+G, 100-B/2);

        if(r < -100-R){
            m += cost[R]-(100+r+R)*R;
        }else if(-100-R <= r && r <= -99){
            m += cost[max(0, -100-r)] + cost[max(0, r+R-1+100)];
        }else{
            m += cost[R]+(r+99)*R;
        }

        if(g < -G){
            m += cost[G]-(g+G)*G;
        }else if(-G <= g && g <= 1){
            m += cost[max(0, -g)] + cost[max(0, g+G-1)];
        }else{
            m += cost[G]+(g-1)*B;
        }

        if(b < 100-B){
            m += cost[B]+(100-b-B)*B;
        }else if(100-B <= b && b <= 101){
            m += cost[max(0, 100-b)] + cost[max(0, b+B-101)];
        }else{
            m += cost[B]+(b-101)*B;
        }

        ans = min(ans, m);
    }

    cout << ans << endl;
}