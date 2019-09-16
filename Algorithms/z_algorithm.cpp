#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void z_algorithm(const string& s, vector<int>& Z){
    const int n = s.size();
    Z = vector<int>(n, 0);
    for(int i = 1, j = 0; i < n; ++i){
        if(i+Z[i-j] < j+Z[j]){
            Z[i] = Z[i-j];
        }else{
            auto k = max(0, j+Z[j]-i);
            while(i+k < n && s[k] == s[i+k]) ++k;
            Z[i] = k;
            j = i;
        }
    }
    Z[0] = n;
}

int main(){
    vector<int> Z;
    string s = "aaabaaaab";

    z_algorithm(s, Z);

    for(const auto& e : Z){
        cout << e << " ";
    }
    cout << endl;
}