#include <iostream>
#include <random>
#include <vector>
#include <numeric>
using namespace std;
#define REP(i,n) for(int i=0;i<int(n);i++)

/* 乱数の準備 */
random_device rnd;
mt19937 mt(rnd());
uniform_real_distribution<> rand01(0,1);

int Choice(double *a, int n)
{
  double b[n-1];
  b[0] = a[0];
  for(int i = 1; i < n-1; i++) b[i] = b[i-1] + a[i];
  double rn = rand01(mt);
  if(rn < b[0]) return 0;
  else if(rn >= b[n-2]) return n-1;
  else REP(i,n-2) if(rn >= b[i] && rn < b[i+1]) return i+1;
}

int main()
{
  int c, m; // cはサイコロの種類の数, mはサイコロの目の種類の数
  cin >> c >> m;

  double rho[c]; // 初期状態の確率
  REP(i,c) cin >> rho[i];
  
  double A[c][c]; // 遷移確率
  REP(i,c) REP(j,c) cin >> A[i][j];

  double B[c][m]; // 出力確率
  REP(i,c) REP(j,m) cin >> B[i][j];

  int n; // 操作回数
  cin >> n;

  int x[n], s[n]; // xは観測結果のサイコロの目, sは観測結果のサイコロの種類

  /* サイコロを転がして結果を得る */
  s[0] = Choice(rho,c);
  x[0] = Choice(B[s[0]],m);
  for(int i = 1; i < n; i++){
    s[i] = Choice(A[s[i-1]],c);
    x[i] = Choice(B[s[i]],m);
  }

  /* 前向きアルゴリズム */
  double C[n];
  double alpha[n][c];
  REP(i,c) alpha[0][i] = rho[i]*B[i][x[0]];
  C[0] = 1.0 / accumulate(&alpha[0][0],&alpha[0][c],0.0);
  REP(i,c) alpha[0][i] *= C[0];
  for(int i = 1; i < n; i++){
    REP(j,c){
      double d = 0.0;
      REP(k,c) d += alpha[i-1][k]*A[k][j];
      alpha[i][j] = d*B[j][x[i]];
    }
    C[i] = 1.0 / accumulate(&alpha[i][0],&alpha[i][c],0.0);
    REP(j,c) alpha[i][j] *= C[i];
  }
  double P_x = 1;
  REP(i,n) P_x *= C[i];
  P_x = 1.0 / P_x;

  cout << "s" << endl;
  REP(i,n){
    cout << s[i] << " ";
    //if(i % 10 == 0) cout << endl;
  }
  
  cout << endl <<  "x" << endl;
  REP(i,n){
    cout << x[i] << " ";
    //if(i % 10 == 0) cout << endl;
  }

  cout << endl << P_x << endl;

  cout << "alpha" << endl;
  REP(i,n){
    REP(j,c){
      cout << alpha[i][j] << " ";
    }
    cout << endl;
  }
}
