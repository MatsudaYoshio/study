#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Imos2D{
private:
    vector<vector<int>> s;
public:
    Imos2D(const vector<vector<int>>& v){
        const int h = v.size();
        const int w = begin(v)->size();
        this->s = vector<vector<int>>(h+1, vector<int>(w+1, 0));

        for(int i = 1; i <= h; ++i){
            copy(begin(v[i-1]), end(v[i-1]), begin(this->s[i])+1);
        }

        for(int i = 0; i <= h; ++i){
            for(int j = 0; j < w; ++j){
                this->s[i][j+1] += this->s[i][j];
            }
        }

        for(int i = 0; i < h; ++i){
            for(int j = 0; j <= w; ++j){
                this->s[i+1][j] += this->s[i][j];
            }
        }
    }

    int sum(const int i, const int j, const int h, const int w){
        return this->s[i+h][j+w] - this->s[i][j+w] + this->s[i][j] - this->s[i+h][j];
    }
};

int main(){
    vector<vector<int>> v = {
        {3, 2, 1},
        {2, 2, 1},
        {1, 1, 1}
    };

    Imos2D imos2d(v);

    cout << imos2d.sum(0,0,3,1) << endl; // (0,0)から縦に3個，横に1個（最左端の一列）
    cout << imos2d.sum(1,1,2,2) << endl; // (1,1)から縦に2個，横に2個（右下四つ）
}