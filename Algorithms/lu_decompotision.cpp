#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <cfloat>
using namespace std;

using Mat2d = vector<vector<double>>;

void lu_decompotision(Mat2d& m){
    const int r = m.size();
    const int c = begin(m)->size();
    const int s = min(r, c);

    vector<int> p(r);
    iota(begin(p), end(p), 0);

    for(int k = 0; k < s; ++k){

        /* ピボットテーブルの更新 */ 
        double max_val = DBL_MIN;
        int max_i;
        for(int i = k; i < r; ++i){
            const double x = fabs(m[p[i]][k]);
            if(x > max_val){
                max_val = x;
                max_i = i;
            }
        }
        swap(p[max_i], p[k]);

        const double w = 1.0/m[p[k]][k];
        for(int i = k+1; i < r; ++i){
            m[p[i]][k] *= w;
            for(int j = k+1; j < c; ++j){
                m[p[i]][j] -= m[p[i]][k]*m[p[k]][j];
            }
        }
    }

    /* 転置行列をかけてない形（転置行列がない（単位行列になっている）時も含む） */
    cout << "<LU or L'U'>" << endl;
    for(const auto& r : m){
        for(const auto& e : r){
            cout << e << " ";
        }
        cout << endl;
    }

    /* 転置行列をかけた形 */
    cout << "<PLU>" << endl;
    Mat2d n(r);
    for(int i = 0; i < r; ++i){
        n[i] = m[p[i]];
    }

    for(const auto& r : n){
        for(const auto& e : r){
            cout << e << " ";
        }
        cout << endl;
    }   
}

int main(){
    Mat2d A = {
        {1, 2, -1},
        {1, 1, 2},
        {-2, -1, 1}
    };

    lu_decompotision(A);
}