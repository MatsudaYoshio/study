#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <cfloat>
using namespace std;

using Mat2d = vector<vector<double>>;

class LUSolver{
private:
int n;
vector<int> p;

void lu_decompotision(Mat2d& m){
    this->n = m.size();

    this->p.resize(n);
    iota(begin(this->p), end(this->p), 0);

    for(int k = 0; k < this->n; ++k){

        /* ピボットテーブルの更新 */ 
        double max_val = DBL_MIN;
        int max_i;
        for(int i = k; i < this->n; ++i){
            const double x = fabs(m[this->p[i]][k]);
            if(x > max_val){
                max_val = x;
                max_i = i;
            }
        }
        swap(this->p[max_i], this->p[k]);

        // if(this->p[k] == 0) Aは正則な正方行列ではない

        const double w = 1.0/m[this->p[k]][k];
        for(int i = k+1; i < this->n; ++i){
            m[this->p[i]][k] *= w;
            for(int j = k+1; j < this->n; ++j){
                m[this->p[i]][j] -= m[this->p[i]][k]*m[this->p[k]][j];
            }
        }
    }
}
public:
/* Aは正方行列で,xとyのサイズも正しいことが前提 */
void solve(Mat2d A, vector<double> y, vector<double>& x){
    this->lu_decompotision(A);

    for(int i = 0; i < this->n; ++i){
        for(int j = 0; j < i; ++j){
            y[this->p[i]] -= A[this->p[i]][j]*y[this->p[j]];
        }
    }

    for(int i = this->n-1; i >= 0; --i){
        for(int j = i+1; j < n; ++j){
            y[this->p[i]] -= A[this->p[i]][j]*y[this->p[j]];
        }
        y[this->p[i]] /= A[this->p[i]][i];
    }

    for(int i = 0; i < this->n; ++i){
        x[i] = move(y[this->p[i]]);
    }
}
};

int main(){
    /* Ax = y を解く */
    Mat2d A = {
        {9, 2, 1, 1},
        {2, 8, -2, 1},
        {-1, -2, 7, -2},
        {1 ,-1, -2, 6}
    };
    vector<double> y = {20, 16, 8, 17};
    vector<double> x(4);

    LUSolver s;
    s.solve(A, y, x);

    for(const auto& e : x){
        cout << e << " ";
    }
    cout << endl;
}