#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

constexpr int MAX_N { 100 };
vector<bool> is_prime(MAX_N, true);

void sieve()
{
  is_prime[0] = is_prime[1] = false;

  for(int i = 2; i <= MAX_N; ++i){
    if(is_prime[i]){
      for(int j = i*2; j <= MAX_N; j += i){
        is_prime[j] = false;
      }
    }
  }
}

int main()
{
  sieve();
  for(int i = 1; i < 12; ++i){
    if(is_prime[i]){
      printf("%d is prime\n", i);
    }else{
      printf("%d is not prime\n", i);
    }
  }
}
