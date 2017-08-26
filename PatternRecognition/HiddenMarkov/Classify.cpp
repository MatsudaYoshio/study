#include <iostream>
#include <random>
#include <vector>
#include <numeric>
#include <cmath>
using namespace std;
#define REP(i,n) for(int i=0;i<int(n);i++)

void observe(vector<double> rho, vector<vector<double> > A, vector<vector<double> > B, vector<int> &s, vector<int> &x)
{
  random_device rnd;
  mt19937 mt(rnd());
  discrete_distribution<double> choose{begin(rho),end(rho)};
  s[0] = choose(mt);
  discrete_distribution<double> roll{begin(B[s[0]]),end(B[s[0]])};
  x[0] = roll(mt);
  for(int i = 1; i < (int)s.size(); i++){
    discrete_distribution<double> choose{begin(A[s[i-1]]),end(A[s[i-1]])};
    s[i] = choose(mt);
    discrete_distribution<double> roll{begin(B[s[i]]),end(B[s[i]])};
    x[i] = roll(mt);
  }
}

double getC(vector<double> v)
{ // スケーリング係数の計算
  return 1.0 / accumulate(begin(v),end(v),0.0);
}

void forward(vector<double> rho, vector<vector<double> > A, vector<vector<double> > B, vector<int> x, vector<vector<double> > &alpha, vector<double> &C)
{ // 前向きアルゴリズム
  int c = alpha[0].size();
  REP(i,c) alpha[0][i] = rho[i]*B[i][x[0]];
  C[0] = getC(alpha[0]);
  REP(i,c) alpha[0][i] *= C[0];
  for(int i = 1; i < (int)alpha.size(); i++){
    REP(j,c){
      double d = 0.0;
      REP(k,c) d += alpha[i-1][k]*A[k][j];
      alpha[i][j] = d*B[j][x[i]];
    }
    C[i] = getC(alpha[i]);
    REP(j,c) alpha[i][j] *= C[i];
  }
}

void backward(vector<vector<double> > A, vector<vector<double> > B, vector<int> x, vector<double> C, vector<vector<double> > &beta)
{ // 後ろ向きアルゴリズム
  int n = beta.size();
  int c = beta[0].size();
  fill(begin(beta[n-1]),end(beta[n-1]),C[n-1]);
  for(int i = n-2; i >= 0; i--){
    REP(j,c){
      REP(k,c) beta[i][j] += A[j][k]*B[k][x[i+1]]*beta[i+1][k];
      beta[i][j] *= C[i];
    }
  }
}

void show(vector<vector<double> > v)
{ // 2次元配列の表示
  for(auto e1 : v){
    for(auto e2 : e1) cout << e2 << " ";
    cout << endl;
  }
}

double log_sum(double sum, const double d)
{
  return sum + log(d);
}

void baumwelch(int n,  vector<double> rho_true, vector<vector<double> > A_true, vector<vector<double> > B_true, vector<double> &rho, vector<vector<double> > &A, vector<vector<double> > &B)
{
  int c = rho.size();
  vector<int> s(n), x(n);
  observe(rho_true,A_true,B_true,s,x);
  
  double logPx = 0;
  
  int T = 150;

  REP(t,T){
    vector<double> C(n);
    vector<vector<double> > alpha(n,vector<double>(c));
    forward(rho,A,B,x,alpha,C);
    
    vector<vector<double> > beta(n,vector<double>(c,0.0));
    backward(A,B,x,C,beta);
    
    vector<vector<double> > A_hat(A.size(),vector<double>(A[0].size()));
    vector<vector<double> > B_hat(B.size(),vector<double>(B[0].size()));
    vector<double> rho_hat(c);

    /* A_hatの計算 */
    REP(i,c){
      REP(j,c){
        double xi = 0.0, d = 0.0;
        REP(k,n-1){
          xi += alpha[k][i]*A[i][j]*B[j][x[k+1]]*beta[k+1][j]*C[k];
          d += alpha[k][i]*beta[k][i];
        }
        A_hat[i][j] = xi/d;
      }
    }

    /* B_hatの計算 */
    REP(i,c){
      REP(j,B[0].size()){
        double d = 0.0, e = 0.0;
        REP(k,n){
          d += (j == x[k])*alpha[k][i]*beta[k][i]/C[k];
          e += alpha[k][i]*beta[k][i]/C[k];
        }
        B_hat[i][j] = d/e;
      }
    }

    /* rho_hatの計算 */
    REP(i,c) rho_hat[i] = alpha[0][i]*beta[0][i]/C[0];

    /* パラメータを更新 */
    A = A_hat;
    B = B_hat;
    rho = rho_hat;

    /* logP(x)の計算 */
    double logPx_hat = -accumulate(begin(C),end(C),0.0,log_sum); 
    if(fabs(logPx_hat-logPx) < 1e-9) break;
    logPx = logPx_hat;
  }
}

int main()
{
  vector<double> rho1{1.0, 0.0, 0.0};
  vector<vector<double> > A1{
    {0.1, 0.7, 0.2},
    {0.2, 0.1, 0.7},
    {0.7, 0.2, 0.1}
  };
  vector< vector<double> > B1{
    {0.9, 0.1},
    {0.6, 0.4},
    {0.1, 0.9}
  };

  vector<double> rho1_est{1.0, 0.0, 0.0};
  vector<vector<double> > A1_est{
    {0.15, 0.60, 0.25},
    {0.25, 0.15, 0.60},
    {0.60, 0.25, 0.15}
  };
  vector< vector<double> > B1_est(3,vector<double>(2,0.5));

  baumwelch(10000,rho1,A1,B1,rho1_est,A1_est,B1_est);
  
  vector<double> rho2{1.0, 0.0, 0.0};
  vector<vector<double> > A2{
    {0.7, 0.2, 0.1},
    {0.1, 0.7, 0.2},
    {0.2, 0.1, 0.7}
  };
  vector< vector<double> > B2{
    {0.9, 0.1},
    {0.6, 0.4},
    {0.1, 0.9}
  };

  vector<double> rho2_est{1.0, 0.0, 0.0};
  vector<vector<double> > A2_est{
    {0.60, 0.25, 0.15},
    {0.15, 0.60, 0.25},
    {0.25, 0.15, 0.60}
  };
  vector< vector<double> > B2_est(3,vector<double>(2,0.5));

   baumwelch(10000,rho2,A2,B2,rho2_est,A2_est,B2_est);
   
   vector<int> testdata1(100), testdata2(100), s_dummy(100);
   vector<vector<double> > alpha_dummy(100,vector<double>(rho1.size()));
   vector<double> C1(100), C2(100);
   double logPx1, logPx2;
   int miss = 0;
   FILE *fp;
   fp = fopen("data_classify.txt","w");
   REP(i,100){
     observe(rho1,A1,B1,s_dummy,testdata1);
     forward(rho1_est,A1_est,B1_est,testdata1,alpha_dummy,C1);
     forward(rho2_est,A2_est,B2_est,testdata1,alpha_dummy,C2);
     logPx1 = -accumulate(begin(C1),end(C1),0.0,log_sum);
     logPx2 = -accumulate(begin(C2),end(C2),0.0,log_sum);
     if(logPx1 < logPx2) miss++;
     fprintf(fp,"%g %g\n",logPx1,logPx2);
   }
   REP(i,100){
     observe(rho2,A2,B2,s_dummy,testdata2);
     forward(rho1_est,A1_est,B1_est,testdata2,alpha_dummy,C1);
     forward(rho2_est,A2_est,B2_est,testdata2,alpha_dummy,C2);
     logPx1 = -accumulate(begin(C1),end(C1),0.0,log_sum);
     logPx2 = -accumulate(begin(C2),end(C2),0.0,log_sum);
     if(logPx1 > logPx2) miss++;
     fprintf(fp,"%g %g\n",logPx1,logPx2);
   }
   cout << miss << endl;
}
