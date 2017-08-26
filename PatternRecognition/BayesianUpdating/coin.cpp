#include <iostream>
#include <random>
#define REP(i,n) for(int (i)=0;(i)<int(n);(i)++)
#define H true
#define T !H
using namespace std;

int main()
{
  double pi[3], theta[3];
  int n;
  cin >> n;
  REP(i,3) cin >> pi[i];
  REP(i,3) cin >> theta[i];
  random_device rnd;
  mt19937 mt(rnd());
  uniform_real_distribution<> rand01(0,1);
  double p[] = {1,1,1};
  FILE *fp;
  fp = fopen("data.txt","w");
  REP(i,n){
    bool x = (rand01(mt) < theta[0]) ? H : T;
    double d = 0;
    REP(j,3) d += p[j]*(x?theta[j]:1-theta[j]);
    REP(j,3) p[j] *= (x?theta[j]:1-theta[j])/d;
    fprintf(fp,"%d", i);
    REP(j,3) fprintf(fp," %g", p[j]);
    fprintf(fp,"\n");
  }
  fclose(fp);
}
