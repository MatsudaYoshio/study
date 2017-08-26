#include <iostream>
#include <random>
#include <cmath>
#define T 0.01
#define REP(i,n) for(int (i)=0;(i)<int(n);(i)++)
using namespace std;

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
  int c, m;
  cin >> c >> m;
  double pi[c];
  double set_pi[c];
  REP(i,c) cin >> set_pi[i];
  REP(i,c) cin >> pi[i];
  double set_theta[c][m];
  REP(i,c) REP(j,m) cin >> set_theta[i][j];
  int n;
  cin >> n;
  int r[m] = {};
  REP(i,n) r[Choice(set_theta[Choice(set_pi,c)],m)]++;
  double p[c][m];
  double lp = 0;
  REP(k,m){
    double pv = 0;
    REP(i,c) pv += pi[i]*set_theta[i][k];
    lp += r[k]*log(pv);
  }
  int t = 1;
  FILE *fp1, *fp2;
  fp1 = fopen("lp_data.txt","w");
  fp2 = fopen("param_data.txt","w");
  while(1){
    fprintf(fp1,"%d",t);
    fprintf(fp1," %g\n",lp);
    fprintf(fp2,"%d",t);
    REP(k,m){
      double d = 0;
      REP(j,c) d += pi[j]*set_theta[j][k];
      REP(i,c) p[i][k] = pi[i]*set_theta[i][k]/d;
    }
    REP(i,c){
      pi[i] = 0;
      REP(k,m) pi[i] += r[k]*p[i][k];
      pi[i] /= n;
      fprintf(fp2," %g",pi[i]);
    }
    fprintf(fp2,"\n");
    double nlp = 0;
    REP(k,m){
      double pv = 0;
      REP(i,c) pv += pi[i]*set_theta[i][k];
      nlp += r[k]*log(pv);
    }
    if(nlp-lp < T) break;
    lp = nlp;
    t++;
  }
  fclose(fp1);
  fclose(fp2);
}
