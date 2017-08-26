#include <iostream>
#include <random>
#include <vector>
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
  vector< vector<int> > M(c,vector<int>(c,0)); // M[i][j]はサイコロをi,jと連続して取り出した回数
  vector<int> N(c,0); // N[i]はサイコロiが出た回数
  vector< vector<int> > L(c,vector<int>(m,0)); // L[i][j]はサイコロiで目kが出た回数

  /* サイコロを転がして結果を得る */
  s[0] = Choice(rho,c);
  x[0] = Choice(B[s[0]],m);
  N[s[0]]++;
  L[s[0]][x[0]]++;
  for(int i = 1; i < n; i++){
    s[i] = Choice(A[s[i-1]],c);
    x[i] = Choice(B[s[i]],m);
    M[s[i-1]][s[i]]++;
    N[s[i]]++;
    L[s[i]][x[i]]++;
  }

  /* 推定するパラメータ */
  vector<double> rho_p(c,0.0);
  double A_p[c][c], B_p[c][m];

  /* 最尤推定 */
  rho_p[s[0]] = 1.0;
  REP(i,c) REP(j,c) A_p[i][j] = (double)M[i][j]/N[i];
  REP(i,c) REP(j,m) B_p[i][j] = (double)L[i][j]/N[i];

  /* A */
  REP(i,c){
    REP(j,c) cout << A_p[i][j] << " ";
    cout << endl;
  }
  
  cout << endl;

  /* B */
  REP(i,c){
    REP(j,m) cout << B_p[i][j] << " ";
    cout << endl;
  }
}
