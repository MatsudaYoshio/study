#include <iostream>
#include <vector>
using namespace std;

constexpr long long int MOD = 1e9+7;

class Enumeration{
private:
    vector<long long int> fact, rfact;

    long long int inverse(const long long int x){
        long long int res = 1;
        long long int k = MOD-2;
        long long int y = x;

        while(k){
            if(k & 1) res = (res*y) % MOD;
            y = (y*y) % MOD;
            k >>= 1;
        }

        return res;
    }
public:
    Enumeration(const long long int n):fact(n), rfact(n){
        this->fact[0] = 1;
        for(int i = 1; i < n; ++i) this->fact[i] = (this->fact[i-1]*i) % MOD;
        
        this->rfact[n-1] = this->inverse(this->fact[n-1]);
        for(int i = n-2; i >= 0; --i) this->rfact[i] = (this->rfact[i+1]*(i+1)) % MOD;
    }

    long long int combination(const long long int n, const long long int k){
        return (this->fact[n]*((this->rfact[n-k]*this->rfact[k]) % MOD)) % MOD;
    }

    long long int permutation(const long long int n, const long long int k){
        return (this->fact[n]*this->rfact[n-k]) % MOD;
    }

    long long int homogenous_product(const long long int n, const long long int k){
        return this->combination(n+k-1, k);
    }
};

int main(){
    long long int R, C, X, Y, D, L;
    cin >> R >> C >> X >> Y >> D >> L;

    Enumeration E(X*Y+1);

    long long int ans = (R-X+1)*(C-Y+1) % MOD;
    if(D+L == X*Y){
        ans = (ans*E.combination(X*Y, D)) % MOD;
    }else{
        long long int sum = 0;
        for(int i = 1; i < (1<<4); ++i){
            long long int tx = X;
            long long int ty = Y;

            if(i & (1<<0)) --tx;
            if(i & (1<<1)) --ty;
            if(i & (1<<2)) --tx;
            if(i & (1<<3)) --ty;

            if(tx <= 0 || ty <= 0) continue;
            if(tx*ty < D+L) continue;

            if(__builtin_popcount(i) & 1){
                sum += (E.combination(tx*ty, D)*E.combination(tx*ty-D, L)) % MOD;
            }else{
                sum -= (E.combination(tx*ty, D)*E.combination(tx*ty-D, L)) % MOD;
            }
            sum = (sum+MOD) % MOD;
        }
        sum = (E.combination(X*Y, D)*E.combination(X*Y-D, L) - sum + MOD) % MOD;
        ans = (ans*sum) % MOD;
    }
    
    cout << ans << endl;
}