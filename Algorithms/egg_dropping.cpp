#include <iostream>
#include <cmath>
using namespace std;

// O(nlogk)

bool C(const int f, const int n, const int k){
    long long int ans = 0;
    double x = 1;  
    for(int i = 1; i <= n && ans <= k; ++i){
        x *= f-i+1;
        x /= i;
        ans += x;
    }

    return ans < k;
}

int main(){
    int n, k; // 卵の数と階数
    cin >> n >> k;

    if(n == 1){
        cout << "Number of drops in the worst case: " << k << endl;
        return 0;
    }else if(n == 2){
        cout << "Number of drops in the worst case: " << static_cast<int>(ceil((sqrt(8*k+1)-1)/2)) << endl;
        return 0;
    }

    int lb = 0, ub = k, mid;

    while(ub - lb > 1){
        mid = (lb + ub)/2;
        if(C(mid, n, k)) lb = mid;
        else ub = mid;
    }

    cout << "Number of drops in the worst case: " << lb+1 << endl;
}