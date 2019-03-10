#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

long long int f(const long long int x){
    const long long int m = log2(x)+1;
    long long int res = 0;
    for(int i = 1; i <= m; ++i){
        long long int n = 1LL<<i;
        long long int c = ((x+1)/n)*(n/2);
        c += max(0LL, ((x+1)%n)-(n/2));

        if(c & 1) res += n>>1;
    }

    return res;
}

int main(){
    long long int A, B;
    cin >> A >> B;

    long long int ans = f(A-1)^f(B);
    cout << ans << endl;
}