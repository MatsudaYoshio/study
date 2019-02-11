#include <iostream>
#include <vector>
using namespace std;

class Enumeration{
private:
    static constexpr long long int MOD = 1e9+7;
    
    vector<long long int> fact, rfact;

    long long int inverse(const long long int x){
        long long int res = 1;
        long long int k = this->MOD-2;
        long long int y = x;

        while(k){
            if(k & 1) res = (res*y) % this->MOD;
            y = (y*y) % this->MOD;
            k >>= 1;
        }

        return res;
    }
public:
    Enumeration(const long long int n):fact(n), rfact(n){
        this->fact[0] = 1;
        for(int i = 1; i < n; ++i) this->fact[i] = (this->fact[i-1]*i) % this->MOD;
        
        this->rfact[n-1] = this->inverse(this->fact[n-1]);
        for(int i = n-2; i >= 0; --i) this->rfact[i] = (this->rfact[i+1]*(i+1)) % this->MOD;
    }

    long long int combination(const long long int n, const long long int k){
        return (this->fact[n]*((this->rfact[n-k]*this->rfact[k]) % this->MOD)) % this->MOD;
    }

    long long int permutation(const long long int n, const long long int k){
        return (this->fact[n]*this->rfact[n-k]) % this->MOD;
    }

    long long int homogenous_product(const long long int n, const long long int k){
        return this->combination(n+k-1, k);
    }
};

int main(){
    Enumeration E(2000001);

    cout << E.combination(1000000, 100) << endl;
    cout << E.permutation(1000000, 100) << endl;
    cout << E.homogenous_product(1000000, 1000000) << endl;
}